/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:31:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/17 14:20:44 by Philip           ###   ########.fr       */
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

#include "functions.h"
#include "minishell/minishell.h"
#include "pipes/pipes.h"
#include "command_list/cmd_list.h"
#include "environment_variables/env.h"
#include "built_in/built_in.h"
#include "signal_handler/signal_handler.h"
#include "exit_status.h"
#include "execution/file_check.h"
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
#include <sys/stat.h> /* stat */
#include <readline/readline.h> /* rl_clear_history */
#include <signal.h>
#include <errno.h>

static int	_open_heredoc_temp_file_for_write(void)
{
	int	fd;

	if (access(HEREDOC_FILE, F_OK | R_OK | W_OK) != 0)
		unlink(HEREDOC_FILE);
	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0755);
	return (fd);
}

int	empty(void)
{
	return (0);
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

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_sigint);
	rl_event_hook = &empty;
	dup2(stdin_copy, STDIN_FILENO);
	rl_outstream = stderr;
	heredoc_fd = _open_heredoc_temp_file_for_write();
	while (minishell()->received_signal == NONE)
	{
		line = readline("> ");
		if (!line)
		{
			ft_dprintf(STDERR_FILENO,
				"minishell: warning: here-document delimited by end-of-line "
				"(wanted `END')\n");
			break ;
		}
		if (minishell()->received_signal == RECEIVED_SIGINT)
			break ;
		if (ft_strncmp(delimiter, line, ft_strlen(delimiter) + 1) == 0)
			break ;
		if (line)
			write(heredoc_fd, line, ft_strlen(line));
		free_and_null((void **)&line);
	}
	close(heredoc_fd);
	free_and_null((void **)&line);
	rl_outstream = stdout;
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
				if (minishell()->received_signal != NONE)
					return ;
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

#include "execution/execution.h"
int	execute_shell_script(const char *filepath)
{
	struct stat	statbuf;

	if (stat(filepath, &statbuf) != 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: No such file or directory\n",
			filepath);
		return (NO_SUCH_FILE_EXIT_STATUS);
	}
	else if (S_ISDIR(statbuf.st_mode))
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: Is a director\n", filepath);
		return (IS_A_DIRECTORY_EXIT_STATUS);
	}
	else if (!(statbuf.st_mode & S_IXUSR) || !(statbuf.st_mode & S_IRUSR))
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: permission denied\n",
			filepath);
		return (PERMISSION_DENIED_EXIT_STATUS);
	}

	pid_t	id;

	id = fork();
	if (id == 0)
		execute_script_child(filepath);
	return (get_last_child_exit_status(id));
}

void	_exec_one_cmd(t_cmd_list *cmd, t_env **env)
{
	int		stdin_copy;
	int		exit_status;
	pid_t	id;
	char	**envp;

	stdin_copy = dup(STDIN_FILENO);
	apply_redirects(cmd, stdin_copy);
	if (cmd->argv && is_builtin_function(cmd->argv[0]))
		exit_status = execute_builtin_function(cmd->argv, env, cmd, NULL);
	else if (cmd->argv && cmd->argv[0] && ft_strlen(cmd->argv[0]) > 0)
	{
		signal(SIGQUIT, waiting_child_sigquit);
		signal(SIGINT, waiting_child_sigint);
		id = fork();
		if (id == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			envp = env_build_envp(*env);
			// [ ] check if command is a folder
			if (execve(cmd->argv[0], cmd->argv, envp) == -1) // [x] free envp when execve fails
			{
				ft_dprintf(STDERR_FILENO, "minishell: %s: "
					"command not found\n", cmd->argv[0]);
				free_cmds_env_pipes_rl_clear_history((t_to_free){.cmds = cmd, .env = *env, .pipes = NULL});
				free_string_array_and_null(&envp);
				exit(COMMAND_NOT_FOUND_EXIT_STATUS);
			}
		}
		exit_status = get_last_child_exit_status(id);
	}
	if (minishell()->received_signal != NONE)
		exit_status = minishell()->exit_status;
	env_update_exit_status(env, exit_status);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
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
	bool		last_command_is_child;

	if (cmd_list_len(cmds) == 1)
		return (_exec_one_cmd(cmds, env));
	last_command_is_child = false;
	exit_status = 0;
	pipes_init(&pipes, cmd_list_len(cmds) - 1);
	cmd = cmds;
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	read_end = -1;
	write_end = -1;
	cmd_idx = 0;
	if (cmd->argv
		&& cmd->argv[0]
		&& ft_strchr(cmds->argv[0], '/')
		&& ft_strlen(cmds->argv[0]) > 3
		&& ft_strncmp(ft_strchr(cmd->argv[0], '\0') - 3, ".sh", 3) == 0)
		return (env_update_exit_status(env, execute_shell_script(cmd->argv[0])));
	while (cmd && minishell()->received_signal == NONE)
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
		if (minishell()->received_signal != NONE)
			break ;

		/* Executes built-ins for main process */
		
		if (cmd->argv && cmd->argv[0] && ft_strlen(cmd->argv[0]) > 0)
		{
			/* signals for parent */
			signal(SIGQUIT, waiting_child_sigquit);
			signal(SIGINT, waiting_child_sigint);
			id = fork();
			if (id == 0)
			{
				signal(SIGQUIT, SIG_DFL);
				signal(SIGINT, SIG_DFL);
				pipes_close_all(&pipes);
				if (is_builtin_function(cmd->argv[0]))
					exit(execute_builtin_function(cmd->argv, env, cmds, &pipes));
				// [x] check if command is a folder
				// [x] try out all the perror messages for this one
				else // [x] free envp when execve fails
				{
					char **envp;

					if (access(cmd->argv[0], F_OK) != 0)
					{
						ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", cmd->argv[0]);
						exit(COMMAND_NOT_FOUND_EXIT_STATUS);
					}
					else if (file_check(cmd->argv[0], CHECK_EXECUTABLE) == IS_A_DIRECTORY)
					{
						ft_dprintf(STDERR_FILENO, "minishell: %s: Is a directory\n", cmd->argv[0]);
						exit(IS_A_DIRECTORY_EXIT_STATUS);
					}
					envp = env_build_envp(*env);
					execve(cmd->argv[0], cmd->argv, envp);
					ft_dprintf(STDERR_FILENO, "minishell: ");
					perror(cmd->argv[0]);
					free_cmds_env_pipes_rl_clear_history((t_to_free){.cmds = cmds, .env = *env, .pipes = &pipes});
					free_string_array_and_null(&envp);
					exit(PERMISSION_DENIED_EXIT_STATUS);
				}
			}
		}
		cmd = cmd->next;
		cmd_idx++;
	}
	/* Reset stdin and stdout for main process */
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);

	if (last_command_is_child)
	{
		exit_status = get_last_child_exit_status(id);
		if (minishell()->received_signal != NONE)
			exit_status = minishell()->exit_status;
		env_update_exit_status(env, exit_status);
	}
	/* waits for all child processes to finish before ending function */
	while (wait(NULL) != -1)
	{
		;
	}

	/* Free resources */
	free_and_null((void **)(&pipes.pipes));
	minishell()->received_signal = NONE;
	unlink(HEREDOC_FILE);
}
