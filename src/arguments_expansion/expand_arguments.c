/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:07:24 by Philip            #+#    #+#             */
/*   Updated: 2024/04/10 01:47:11 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_expand_string.h"
#include "../command_list/cmd_list.h"
#include "../environment_variables/env.h"
#include <stddef.h>

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
