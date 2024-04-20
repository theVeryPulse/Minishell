/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _execute_one_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 23:40:44 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 14:08:59 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_execution.h" /* _apply_redirects */
#include "../minishell/minishell.h" /* minishell */
#include "../command_list/t_cmd_list.h" /* t_cmd_list */
#include "../environment_variables/env.h" /* env_update_exit_status */
#include "built_in/built_in.h" /* is_builtin_function */
#include "../signal_handler/signal_handler.h" /* sigint_sigquit_handler */
#include <sys/types.h> /* pid_t */
#include <stddef.h> /* NULL */
#include <unistd.h> /* fork */

extern void	_execute_one_command(t_cmd_list *cmd, t_env **env)
{
	int		exit_status;
	pid_t	id;

	exit_status = 0;
	_stdin_stdout(BACKUP);
	_apply_redirects(cmd);
	if (minishell()->received_signal != NONE)
		exit_status = minishell()->exit_status;
	else if (cmd->argv && cmd->argv[0] && is_builtin_function(cmd->argv[0]))
		exit_status = _execute_builtin_function(cmd->argv, env, cmd, NULL);
	else if (cmd->argv && cmd->argv[0])
	{
		sigint_sigquit_handler(WAITING_CHILD);
		id = fork();
		if (id == 0)
		{
			sigint_sigquit_handler(DEFAULT);
			_child_execute_target_command(cmd, *env, NULL);
		}
		exit_status = _exit_status(id);
	}
	env_update_exit_status(env, exit_status);
	_stdin_stdout(RESET_FROM_BACKUP);
	_stdin_stdout(CLOSE_BACKUP);
}
