/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:31:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 16:10:44 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* 

For debugging child process:

{
	// https://sourceware.org/gdb/onlinedocs/gdb/Forks.html
	"description": "Fork follows Child process",
	"text": "set follow-fork-mode child",
	"ignoreFailures": true
},
{
	// https://sourceware.org/gdb/onlinedocs/gdb/Forks.html
	"description": "Fork will keep the other process attached to debugger",
	"text": "set detach-on-fork off",
	"ignoreFailures": true
}

 */

// #include
#include "pipes/pipes.h"
#include "command_list/cmd_list.h"
#include "environment_variables/env.h"
#include "built_in/built_in.h"
#include "libft.h"
#include "free/free.h"
#include "heredoc.h"
#include "get_last_child_exit_status.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <readline/readline.h> /* rl_clear_history */

static int	_open_heredoc_temp_file_for_write(void)
{
	int		fd;

	if (access(HEREDOC_FILE, F_OK | R_OK | W_OK) != 0)
		unlink(HEREDOC_FILE);
	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0755);
	return (fd);
}

/**
 * @brief 
 * 
 * @param delimiter 
 * @note The process itself first finishes heredoc before executing any built-in
 *       or external programs.
 * @todo Handle signals
 */
void	heredoc(char *delimiter, int stdin_copy)
{
	char	*line;
	int		heredoc_fd;
	char	*delimiter_nl;

	dup2(stdin_copy, STDIN_FILENO);
	delimiter_nl = ft_format_string("%s\n", delimiter);
	heredoc_fd = _open_heredoc_temp_file_for_write();
	// ft_dprintf(STDERR_FILENO, "  %d heredoc\n", getpid()); /* Develop */
	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		// ft_dprintf(STDERR_FILENO, "  %d received \"%s\"\n", getpid(), line); /* Develop */
		if (!line)
		{
			ft_dprintf(STDERR_FILENO,
				"\nminishell: warning: here-document delimited by end-of-line "
				"(wanted `END')\n");
			break ;
		}
		if (ft_strncmp(delimiter_nl, line, ft_strlen(delimiter) + 1) == 0)
			break ;
		if (line)
			write(heredoc_fd, line, ft_strlen(line));
		free_and_null((void **)&line);
	}
	close(heredoc_fd);
	free_and_null((void **)&delimiter_nl);
	free_and_null((void **)&line);
}

/**
 * @brief 
 * 
 * @param 
 * @note Four occasions: 
 *       `<`  : dup2(input_file_fd, STDIN_FILENO)
 *       `<<` : dup2(heredoc_temp_file, STDIN_FILENO)
 *       `>`  : dup2(output_file_fd, STDOUT_FILENO) O_WRONLY | O_APPEND
 *       `>>` : dup2(output_file_fd, STDOUT_FILENO) O_WRONLY | O_TRUNC
 */
void	apply_redirects(t_cmd_list *cmd, int stdin_copy)
{
	char	**redirect;
	int		fd;

	if (!cmd->redirects)
		return ;
	redirect = cmd->redirects;
	while (*redirect)
	{
		if ((*redirect)[0] == '<')
		{
			if ((*redirect)[1] == '<')
			{
				// ft_dprintf(STDERR_FILENO, "  %d executing heredoc\n", getpid()); /* Develop */
				heredoc(&(*redirect)[2], stdin_copy);
				fd = open(HEREDOC_FILE, O_RDONLY);
			}
			else
				fd = open(&(*redirect)[1], O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
		else if ((*redirect)[0] == '>')
		{
			if ((*redirect)[1] == '>')
				fd = open(&(*redirect)[2], O_WRONLY | O_APPEND);
			else
				fd = open(&(*redirect)[1], O_WRONLY | O_TRUNC);
			dup2(fd, STDOUT_FILENO);
		}
		close(fd);
		redirect++;
	}
}

void	execute_cmds(t_cmd_list *cmds, t_env **env)
{
	t_pipes		pipes;
	t_cmd_list	*cmd;
	int			stdin_copy;
	int			stdout_copy;
	int			read_end;
	int			write_end;
	int			cmd_idx;
	pid_t		id;
	int			exit_status;

	exit_status = 0;
	pipes_init(&pipes, cmd_list_len(cmds) - 1);
	cmd = cmds;
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	read_end = -1;
	write_end = -1;
	cmd_idx = 0;
	while (cmd)
	{
		/* Reset STDIN and STDOUT for the process */
		dup2(stdin_copy, STDIN_FILENO);
		dup2(stdout_copy, STDOUT_FILENO);

		/* Skip commands that have redirect issues */
		if (cmd->should_execute == false)
		{
			cmd = cmd->next;
			continue ;
		}

		/* Set up pipes and redirects before fork and execute */
		read_end = cmd_idx * 2 - 2;
		write_end = cmd_idx * 2 + 1;
		if (write_end >= 0 && write_end < pipes.pipe_count * 2)
		{
			dup2(pipes.pipes[write_end], STDOUT_FILENO);
			close(pipes.pipes[write_end]);
		}
		if (read_end >= 0 && read_end < pipes.pipe_count * 2)
		{
			dup2(pipes.pipes[read_end], STDIN_FILENO);
			close(pipes.pipes[read_end]);
		}
		apply_redirects(cmd, stdin_copy);


		/* Executes built-ins for main process */
		if (cmd->argv && cmd->argv[0] && is_builtin_function(cmd->argv[0]))
			exit_status = exec_builtin_function(cmd->argv, env, cmds, &pipes);
		else if (cmd->argv && cmd->argv[0] && ft_strlen(cmd->argv[0]) > 0)
		{
			id = fork();
			if (id == 0)
			{
				char **envp;

				envp = env_build_envp(*env);
				pipes_close_all(&pipes);
				if (execve(cmd->argv[0], cmd->argv, envp) == -1) // [x] free envp when execve fails
				{
					ft_dprintf(STDERR_FILENO, "minishell: %s: "
						"command not found\n", cmd->argv[0]);
					rl_clear_history();
					env_free(env);
					cmd_list_free(&cmds);
					free_string_array_and_null(&envp);
					exit (127);
				}
			}
			else
				exit_status = get_last_child_exit_status(id);
		}
		
		cmd = cmd->next;
		cmd_idx++;
	}
	/* Reset stdin and stdout for main process */
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);

	// printf("Exit status: %d\n", exit_status);/* Testing */
	/* Update $? */
	char	*exit_status_str;
	char	*exit_status_name_value;

	exit_status_str = ft_itoa(exit_status);
	exit_status_name_value = ft_format_string("?=%s", exit_status_str);
	env_update_name_value(env, exit_status_name_value);
	free_and_null((void **)&exit_status_str);
	free_and_null((void **)&exit_status_name_value);

	/* Free resources */
	free_and_null((void **)(&pipes.pipes));
	unlink(HEREDOC_FILE);
}
