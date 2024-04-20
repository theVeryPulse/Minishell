/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _execute_multiple_commands.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 23:45:13 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 14:08:52 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_execution.h" /* _exit_status, */
#include "../minishell/minishell.h" /* minishell */
#include "../command_list/cmd_list.h" /* cmd_list_len */
#include "../environment_variables/env.h" /* env_update_exit_status */
#include "../pipes/pipes.h" /* pipes_init */
#include "built_in/built_in.h" /* is_builtin_function */
#include "../signal_handler/signal_handler.h"
#include "t_fd_action.h" /* sigint_sigquit_handler */
#include "../free/free.h" /* free_and_null */
#include "_heredoc.h" /* HEREDOC_FILE */
#include "libft.h" /* ft_strlen */
#include <readline/readline.h> /* rl_clear_history */
#include <stdlib.h> /* exit */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h> /* wait */
#include <unistd.h> /* STDIN_FILENO, STDOUT_FILENO */

extern void		_execute_multiple_commands(t_cmd_list *cmds, t_env **env);
static pid_t	_execute_commands_with_pipes_redirects(t_cmd_list *cmds,
					t_env **env, t_pipes *pipes);
static pid_t	_fork_and_execute_command(t_cmd_list *cmd, t_cmd_list *cmds,
					t_env **env, t_pipes *pipes);
static void		_apply_pipes(t_pipes *pipes, int cmd_idx);

extern void	_execute_multiple_commands(t_cmd_list *cmds, t_env **env)
{
	t_pipes		pipes;
	pid_t		id;

	pipes_init(&pipes, cmd_list_len(cmds) - 1);
	_stdin_stdout(BACKUP);
	id = _execute_commands_with_pipes_redirects(cmds, env, &pipes);
	_stdin_stdout(RESET_FROM_BACKUP);
	_stdin_stdout(CLOSE_BACKUP);
	env_update_exit_status(env, _exit_status(id));
	while (wait(NULL) != -1)
		;
	free_and_null((void **)(&pipes.pipes));
	unlink(HEREDOC_FILE);
}

static pid_t	_execute_commands_with_pipes_redirects(t_cmd_list *cmds,
	t_env **env, t_pipes *pipes)
{
	t_cmd_list	*cmd;
	int			cmd_idx;
	pid_t		id;

	cmd = cmds;
	cmd_idx = 0;
	while (cmd && minishell()->received_signal == NONE)
	{
		_stdin_stdout(RESET_FROM_BACKUP);
		if (cmd->has_invalid_redirects)
		{
			cmd = cmd->next;
			cmd_idx++;
			continue ;
		}
		_apply_pipes(pipes, cmd_idx);
		_apply_redirects(cmd);
		if (minishell()->received_signal != NONE)
			break ;
		if (cmd->argv && cmd->argv[0] && ft_strlen(cmd->argv[0]) > 0)
			id = _fork_and_execute_command(cmd, cmds, env, pipes);
		cmd = cmd->next;
		cmd_idx++;
	}
	return (id);
}

static pid_t	_fork_and_execute_command(t_cmd_list *cmd, t_cmd_list *cmds,
	t_env **env, t_pipes *pipes)
{
	pid_t	id;
	int		exit_status;

	exit_status = 0;
	sigint_sigquit_handler(WAITING_CHILD);
	id = fork();
	if (id == 0)
	{
		sigint_sigquit_handler(DEFAULT);
		pipes_close_all(pipes);
		if (is_builtin_function(cmd->argv[0]))
		{
			exit_status = _execute_builtin_function(cmd->argv, env, cmds,
					pipes);
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

static void	_apply_pipes(t_pipes *pipes, int cmd_idx)
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
