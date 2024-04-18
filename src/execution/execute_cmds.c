/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:31:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/18 19:58:13 by Philip           ###   ########.fr       */
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

#include "execution.h"
#include "file_check.h"
#include "_heredoc.h" /* HEREDOC_FILE */
#include "../functions.h"
#include "../minishell/minishell.h"
#include "../pipes/pipes.h"
#include "../command_list/cmd_list.h"
#include "../environment_variables/env.h"
#include "../built_in/built_in.h"
#include "../signal_handler/signal_handler.h"
#include "../exit_status.h"
#include "../free/free.h"
#include "t_fd_action.h"
#include "libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <readline/readline.h> /* rl_clear_history */
#include <signal.h>
#include <errno.h>


void	_set_up_pipes(t_pipes *pipes, int cmd_idx)
{
	int	read_end;
	int	write_end;

	read_end = cmd_idx * 2 - 2;
	write_end = cmd_idx * 2 + 1;
	if (write_end >= 0 && write_end < pipes->pipe_count * 2)
	{
		dup2(pipes->pipes[write_end], STDOUT_FILENO);
		close(pipes->pipes[write_end]);
	}
	if (read_end >= 0 && read_end < pipes->pipe_count * 2)
	{
		dup2(pipes->pipes[read_end], STDIN_FILENO);
		close(pipes->pipes[read_end]);
	}
}

// [ ] Left here: env and cmds can also be sent as arguments
pid_t	_fork_and_execute_command(t_cmd_list *cmd, t_cmd_list *cmds, t_env **env, t_pipes *pipes)
{
	pid_t	id;
	int		exit_status;

	exit_status = 0;
	signal(SIGQUIT, waiting_child_sigquit);
	signal(SIGINT, waiting_child_sigint);
	id = fork();
	if (id == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		pipes_close_all(pipes);
		if (is_builtin_function(cmd->argv[0]))
		{
			exit_status = execute_builtin_function(cmd->argv, env, cmds, pipes);
			rl_clear_history();
			free_cmds_env_pipes_rl_clear_history((t_to_free){.pipes = pipes,
				.cmds = cmds, .env = *env});
			exit(exit_status);
		}
		else
			_child_execute_target_command(cmd, *env, pipes);
	}
	return (id);
}

int	_stdin_stdout(t_fd_action action)
{
	static int	stdin_copy = -1;
	static int	stdout_copy = -1;

	if (action == BACKUP)
	{
		stdin_copy = dup(STDIN_FILENO);
		stdout_copy = dup(STDOUT_FILENO);
	}
	else if (action == RESET_FROM_BACKUP)
	{
		dup2(stdin_copy, STDIN_FILENO);
		dup2(stdout_copy, STDOUT_FILENO);
	}
	else if (action == CLOSE_BACKUP)
	{
		close(stdin_copy);
		close(stdout_copy);
		stdin_copy = -1;
		stdout_copy = -1;
	}
	else if (action == LOOKUP_STDIN)
		return (stdin_copy);
	return (-1);
}

void	_execute_one_command(t_cmd_list *cmd, t_env **env)
{
	int		exit_status;
	pid_t	id;

	exit_status = 0;
	_stdin_stdout(BACKUP);
	_apply_redirects(cmd);
	if (cmd->argv && cmd->argv[0] && is_builtin_function(cmd->argv[0]))
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
			_child_execute_target_command(cmd, *env, NULL);
		}
		exit_status = _exit_status(id);
	}
	env_update_exit_status(env, exit_status);
	_stdin_stdout(RESET_FROM_BACKUP);
	_stdin_stdout(CLOSE_BACKUP);
}

bool	_is_shell_script(const char **argv)
{
	return (argv
		&& argv[0]
		&& ft_strchr(argv[0], '/')
		&& ft_strlen(argv[0]) > 2
		&& ft_strncmp(ft_strchr(argv[0], '\0') - 3, ".sh", 3) == 0);
}

void	_execute_multiple_commands() // [ ] Left here
{
	pipes_init(&pipes, cmd_list_len(cmds) - 1);
	_stdin_stdout(BACKUP);
	cmd_idx = 0;
	while (cmd && minishell()->received_signal == NONE)
	{
		_stdin_stdout(RESET_FROM_BACKUP);
		if (cmd->has_invalid_redirects)
		{
			cmd = cmd->next;
			continue ;
		}
		_set_up_pipes(&pipes, cmd_idx);
		_apply_redirects(cmd);
		if (minishell()->received_signal != NONE)
			break ;
		if (cmd->argv && cmd->argv[0] && ft_strlen(cmd->argv[0]) > 0)
			id = _fork_and_execute_command(cmd, cmds, env, &pipes);
		cmd = cmd->next;
		cmd_idx++;
	}
	_stdin_stdout(RESET_FROM_BACKUP);
	_stdin_stdout(CLOSE_BACKUP);
	env_update_exit_status(env, _exit_status(id));
	while (wait(NULL) != -1)
		;
	free_and_null((void **)(&pipes.pipes));
	minishell()->received_signal = NONE;
	unlink(HEREDOC_FILE);
}

// [ ] start debugging stdin_stdout functions from here
void	execute_cmds(t_cmd_list *cmds, t_env **env)
{
	t_pipes		pipes;
	t_cmd_list	*cmd;
	int			cmd_idx;
	pid_t		id;

	cmd = cmds;
	if (_is_shell_script((const char **)cmd->argv))
		return (_execute_shell_script(cmd->argv[0], env));
	else if (cmd_list_len(cmds) == 1)
		return (_execute_one_command(cmds, env));
	else
		_execute_multiple_commands();
	// <<<<<<
	pipes_init(&pipes, cmd_list_len(cmds) - 1);
	_stdin_stdout(BACKUP);
	cmd_idx = 0;
	while (cmd && minishell()->received_signal == NONE)
	{
		_stdin_stdout(RESET_FROM_BACKUP);
		if (cmd->has_invalid_redirects)
		{
			cmd = cmd->next;
			continue ;
		}
		_set_up_pipes(&pipes, cmd_idx);
		_apply_redirects(cmd);
		if (minishell()->received_signal != NONE)
			break ;
		if (cmd->argv && cmd->argv[0] && ft_strlen(cmd->argv[0]) > 0)
			id = _fork_and_execute_command(cmd, cmds, env, &pipes);
		cmd = cmd->next;
		cmd_idx++;
	}
	_stdin_stdout(RESET_FROM_BACKUP);
	_stdin_stdout(CLOSE_BACKUP);
	env_update_exit_status(env, _exit_status(id));
	while (wait(NULL) != -1)
		;
	free_and_null((void **)(&pipes.pipes));
	minishell()->received_signal = NONE;
	unlink(HEREDOC_FILE);
	// <<<<<<
}
