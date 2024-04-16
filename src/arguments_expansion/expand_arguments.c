/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:07:24 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 01:09:06 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_expand_string.h"
#include "../command_list/cmd_list.h"
#include "../environment_variables/t_env.h"
#include <stddef.h>

static void	_shift_all_following_args_left(char **argv, int i);

/**
 * @brief Expands environment variables in command arguments and redirects.
 *
 * @param cmds A pointer to the head of the linked list of command nodes.
 * @param env  A pointer to the head of the linked list of environment
 *             variables.
 */
void	expand_arguments(t_cmd_list *cmds, t_env *env)
{
	t_cmd_list	*cmd;
	int			i;

	cmd = cmds;
	while (cmd)
	{
		i = 0;
		while (cmd->cmd_argv && cmd->cmd_argv[i])
		{
			_expand_string(&(cmd->cmd_argv[i]), env);
			/* [x] if a $VAR expands to NULL, shifts all args leftward one position */
			if (cmd->cmd_argv[i] == NULL)
				_shift_all_following_args_left(cmd->cmd_argv, i);
			i++;
		}
		i = 0;
		while (cmd->redirects && cmd->redirects[i])
		{
			_expand_string(&(cmd->redirects[i]), env);
			i++;
		}
		cmd = cmd->next;
	}
}

static void	_shift_all_following_args_left(char **argv, int i)
{
	argv[i] = argv[i + 1];
	while (argv[i])
	{
		argv[i] = argv[i + 1];
		i++;
	}
}
