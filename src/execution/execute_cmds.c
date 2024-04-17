/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:31:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/17 23:42:09 by Philip           ###   ########.fr       */
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
pid_t	_fort_and_execute_command(t_cmd_list *cmd, t_pipes *pipes)
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
			exit_status = execute_builtin_function(cmd->argv, minishell()->env,
				minishell()->cmds, pipes);
			rl_clear_history();
			free_cmds_env_pipes_rl_clear_history((t_to_free){.pipes = pipes,
				.cmds = minishell()->cmds, .env = minishell()->env});
			exit(exit_status);
		}
		else // [x] free envp when execve fails
			_child_execute_target_command(cmd, *env, &pipes);
	}

}

void	execute_cmds(t_cmd_list *cmds, t_env **env)
{
	t_pipes		pipes;
	t_cmd_list	*cmd;
	int			stdin_copy;
	int			stdout_copy;
	int			cmd_idx;
	pid_t		id;
	int			exit_status;

	cmd = cmds;
	if (cmd->argv
		&& cmd->argv[0]
		&& ft_strchr(cmds->argv[0], '/')
		&& ft_strlen(cmds->argv[0]) > 3
		&& ft_strncmp(ft_strchr(cmd->argv[0], '\0') - 3, ".sh", 3) == 0)
		return (env_update_exit_status(env, _execute_shell_script(cmd->argv[0])));
	if (cmd_list_len(cmds) == 1)
		return (_execute_one_command(cmds, env));
	exit_status = 0;
	pipes_init(&pipes, cmd_list_len(cmds) - 1);
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	cmd_idx = 0;
	while (cmd && minishell()->received_signal == NONE)
	{
		/* Reset STDIN and STDOUT for the process */
		dup2(stdin_copy, STDIN_FILENO);
		dup2(stdout_copy, STDOUT_FILENO);

		/* Skip commands that have redirect issues */
		if (cmd->has_invalid_redirects)
		{
			cmd = cmd->next;
			continue ;
		}
		_set_up_pipes(&pipes, cmd_idx);
		_apply_redirects(cmd, stdin_copy);
		if (minishell()->received_signal != NONE)
			break ;

		/* Execution */
		if (cmd->argv && cmd->argv[0] && ft_strlen(cmd->argv[0]) > 0)
		{
			// REFACTOR
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
				{
					exit_status = execute_builtin_function(cmd->argv, env, cmds, &pipes);
					rl_clear_history();
					free_cmds_env_pipes_rl_clear_history((t_to_free){.cmds = cmds, .env = *env, .pipes = &pipes});
					exit(exit_status);
				}
				else // [x] free envp when execve fails
					_child_execute_target_command(cmd, *env, &pipes);
				// REFACTOR
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

	exit_status = get_last_child_exit_status(id);
	if (minishell()->received_signal != NONE)
		exit_status = minishell()->exit_status;
	env_update_exit_status(env, exit_status);

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
