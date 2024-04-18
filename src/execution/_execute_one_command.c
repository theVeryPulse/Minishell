/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _execute_one_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:35:39 by Philip            #+#    #+#             */
/*   Updated: 2024/04/18 12:46:24 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../command_list/cmd_list.h"
#include "../environment_variables/env.h"
#include "../minishell/minishell.h"
#include "../signal_handler/signal_handler.h"
#include "../built_in/built_in.h"
#include <signal.h> /* signal */
#include <unistd.h> /* dup, dup2 */
#include <sys/types.h> /* pid_t */

void	_execute_one_command(t_cmd_list *cmd, t_env **env)
{
	int		stdin_copy;
	int		exit_status;
	pid_t	id;

	exit_status = 0;
	stdin_copy = dup(STDIN_FILENO);
	_apply_redirects(cmd, stdin_copy);
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
		// [ ] _exit_status
		// <<<<<<
		exit_status = get_last_child_exit_status(id);
		if (minishell()->received_signal != NONE)
			exit_status = minishell()->exit_status;
		// <<<<<<
	}
	env_update_exit_status(env, exit_status);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
}
