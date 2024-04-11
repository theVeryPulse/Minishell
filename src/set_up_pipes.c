/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:31:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/11 23:43:48 by Philip           ###   ########.fr       */
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
#include "pipes.h"
#include "command_list/cmd_list.h"
#include "environment_variables/env.h"
#include "built_in/built_in.h"
#include "libft.h"
#include "is_builtin_function.h"
#include "free_and_null.h"
#include "fcntl.h"
#include "heredoc.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

static int	_open_heredoc_temp_file_for_write(void)
{
	int		fd;
	char	*heredoc_temp;
	
	heredoc_temp = "./.heredoc_temp";
	if (access(heredoc_temp, F_OK | R_OK | W_OK) != 0)
		unlink(heredoc_temp);
	fd = open(heredoc_temp, O_CREAT | O_WRONLY | O_TRUNC, 0755);
	return (fd);
}

/**
 * @brief Set the up pipes object
 * 
 * @param cmds 
 * @return int* 
 * @note 
 * 
 * cmd_count 3
 * pipes = [0] [1] [2] [3] [4] [5]
 */
void	pipes_init(t_pipes *pipes, int pipe_count)
{
	int	i;

	if (pipe_count < 1)
	{
		pipes->pipe_count = 0;
		pipes->pipes = NULL;
		return ;
	}
	pipes->pipe_count = pipe_count;
	pipes->pipes = (int *)ft_calloc(pipe_count * 2, sizeof(int));
	i = 0;
	while (i < pipe_count * 2)
	{
		pipe(&(pipes->pipes[i]));
		i += 2;
	}
}

void	pipes_close_all(t_pipes *pipes)
{
	int	i;
	
	i = 0;
	while (i < pipes->pipe_count * 2)
		close(pipes->pipes[i++]);
}

/**
 * @brief 
 * 
 * @note
 * cd with only a relative or absolute path  same process
 * export with no options                    same process
 * unset with no options                     same process
 * exit with no options                      same process
 * pwd with no options                       child process
 * env with no options or arguments          child process
 */
bool	command_for_parent_process(const char *cmd)
{
	return (ft_strncmp(cmd, "cd", 3) == 0
			|| ft_strncmp(cmd, "exit", 5) == 0
			|| ft_strncmp(cmd, "unset", 6) == 0
			|| ft_strncmp(cmd, "export", 7) == 0);
}

/**
 * @brief 
 * 
 * @param delimiter 
 * @note The process itself first finishes heredoc before executing any built-in
 *       or external programs.
 * @todo Handle signals
 */
void	heredoc(char *delimiter)
{
	char	*line;
	int		heredoc_fd;
	char	*delimiter_nl;

	delimiter_nl = ft_format_string("%s\n", delimiter);
	heredoc_fd = _open_heredoc_temp_file_for_write();
	printf("  %d heredoc\n", getpid());
	while (1)
	{
		// write(STDERR_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		ft_dprintf(STDERR_FILENO, "  %d received \"%s\"\n", getpid(), line);
		if (!line)
		{
			ft_dprintf(STDERR_FILENO,
				"minishell: warning: here-document delimited by end-of-line"
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
void	apply_redirects(t_cmd_list *cmd)
{
	char	**redirect;
	int		fd;
	int		heredoc_lock;

	if (!cmd->redirects)
		return ;
	redirect = cmd->redirects;
	while (*redirect)
	{
		/* if ((*redirect)[0] == '<' && (*redirect)[1] == '<')
		{
			heredoc(&(*redirect)[2]);
			fd = open(HEREDOC_FILE, O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
		else if ((*redirect)[0] == '<')
		{
			fd = open(&(*redirect)[1], O_RDONLY);
			dup2(fd, STDIN_FILENO);
		} */

		if ((*redirect)[0] == '<')
		{
			if ((*redirect)[1] == '<')
			{
				heredoc_lock= - 1;
				while (heredoc_lock == -1)
				{
					heredoc_lock = open("./.heredoc_lock", O_CREAT | O_EXCL, 0755);
				}
				ft_dprintf(STDERR_FILENO, "  %d has created heredoc_lock\n", getpid());
				heredoc(&(*redirect)[2]); // O_EXCL
				close(heredoc_lock);
				unlink("./.heredoc_lock");
				fd = open(HEREDOC_FILE, O_RDONLY);
			}
			else
				fd = open(&(*redirect)[1], O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}

		/* else if ((*redirect)[0] == '>' && (*redirect)[1] == '>')
		{
			fd = open(&(*redirect)[2], O_WRONLY | O_APPEND);
			dup2(fd, STDOUT_FILENO);
		}
		else if ((*redirect)[0] == '>')
		{
			fd = open(&(*redirect)[1], O_WRONLY | O_TRUNC);
			dup2(fd, STDOUT_FILENO);
		} */

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

void	execute_one_cmd(t_cmd_list *cmd, t_env *env)
{
	pid_t	id;
	int		wstatus;
	int		exit_status;
	char	*exit_status_as_str;
	char	*exit_status_env;

	if (!cmd->cmd_argv && cmd->redirects)
	{
		apply_redirects(cmd);
	}
	else if (command_for_parent_process(cmd->cmd_argv[0]))
	{
		;
	}
	else if (is_builtin_function(cmd->cmd_argv[0]))
	{
		if (ft_strncmp(cmd->cmd_argv[0], "pwd", 3) == 0)
			builtin_pwd();
	}
	else 
	{
		id = fork();
		if (id == 0)
		{
			ft_dprintf(STDERR_FILENO, "  child: %d of %d\n", getpid(), getppid());
			apply_redirects(cmd);
			if (execve(cmd->cmd_argv[0], cmd->cmd_argv, env_build_envp(env)) == -1)
			{
				ft_dprintf(STDERR_FILENO, "minishell: ");
				perror(cmd->cmd_argv[0]);
				exit (127);
			}
			exit (0);
		}
		else
		{
			exit_status = 0;
			waitpid(id, &wstatus, 0);
			if (WIFEXITED(wstatus))
				exit_status = WEXITSTATUS(wstatus);
			printf("Exit status: %d\n", exit_status);
			exit_status_as_str = ft_itoa(exit_status);
			exit_status_env =  ft_format_string("?=%s", exit_status_as_str);
			env_update_name_value(&env, exit_status_env);
			free(exit_status_as_str);
			free(exit_status_env);
			unlink(HEREDOC_FILE);
		}
	}
}

void	execute_cmds(t_cmd_list *cmds, t_env *env)
{
	t_pipes		pipes;
	t_cmd_list	*cmd;
	int			pipe_idx;
	int			cmd_idx;
	pid_t		id;
	int			wstatus;
	int			exit_status;

	unlink("./.heredoc_lock");
	printf("Execution\n");
	if (cmd_list_len(cmds) == 1)
	{
		execute_one_cmd(cmds, env);
		return ;
	}
	pipes_init(&pipes, cmd_list_len(cmds) - 1);
	pipe_idx = 0;
	cmd_idx = 0;
	cmd = cmds;
	while (cmd)
	{
		if (cmd->cmd_argv)
			printf("  executing %s\n", cmd->cmd_argv[0]);
		if (!cmd->should_execute)
		{
			cmd = cmd->next;
			continue ;
		}
		if (cmd->cmd_argv && command_for_parent_process(cmd->cmd_argv[0]))
		{
			/* built-in functions that do not need redirect or pipe */
		}
		else
		{
			id = fork();
			if (id == 0)
			{
				ft_dprintf(STDERR_FILENO, "  child: %d of %d\n", getpid(), getppid());
				/* Set up the pipes */
				/* cmd0 -> pipe[1] -> pipe [0] -> cmd1 -> pipe[3] ->pipe[2] -> cmd2 -> pipe[5] -> pipe[4] -> cmd3 */
				int	read_end;
				int	write_end;
				
				read_end = cmd_idx * 2 - 2; /* (cmd_idx*2-1):last command write */
				write_end = cmd_idx * 2 + 1; /* (cmd_idx*2+0) next command read */
				if (write_end >= 0 && write_end < pipes.pipe_count * 2) /* Each pipe has two ends hence `pipe_count * 2` */
					dup2(pipes.pipes[write_end], STDOUT_FILENO);
				if (read_end >= 0 && read_end < pipes.pipe_count * 2)
					dup2(pipes.pipes[read_end], STDIN_FILENO);
				apply_redirects(cmd);
				pipes_close_all(&pipes);
				ft_dprintf(STDERR_FILENO, "  execve %s\n", cmd->cmd_argv[0]);
				if (execve(cmd->cmd_argv[0], cmd->cmd_argv, env_build_envp(env)) == -1)
				{
					ft_dprintf(STDERR_FILENO, "minishell: ");
					perror(cmd->cmd_argv[0]);
					exit (127);
				}
				exit (0);
			}
		}
		cmd_idx++;
		pipe_idx += 2;
		cmd = cmd->next;
	}
	pipes_close_all(&pipes);
	waitpid(id, &wstatus, 0);
	while (wait(NULL) != -1)
		;
	unlink(HEREDOC_FILE);
	exit_status = 0;
	if (WIFEXITED(wstatus))
		exit_status = WEXITSTATUS(wstatus);
	printf("Exit status: %d\n", exit_status);

	char	*exit_status_as_str;
	char	*exit_status_env;

	exit_status_as_str = ft_itoa(exit_status);
	exit_status_env =  ft_format_string("?=%s", exit_status_as_str);
	env_update_name_value(&env, exit_status_env);
	free(exit_status_as_str);
	free(exit_status_env);
}
