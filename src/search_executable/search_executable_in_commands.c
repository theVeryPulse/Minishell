/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_executable_in_commands.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:27:01 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 19:19:45 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "search_executable.h"
#include "../environment_variables/t_env.h"
#include "../execution/built_in/built_in.h" /* is_builtin_function */
#include "libft.h"

/**
 * @brief Searches for executable files in the directories specified by the PATH
 *        environment variable. If executable is found, the file path will
 *        replace the original argument. Built-in functions will be skipped.
 *
 * @param cmds A pointer to the head of the linked list of command nodes.
 * @param env A pointer to the head of the linked list of environment variables.
 */
extern void	search_executable_in_commands(t_cmd_list *cmds, t_env *env)
{
	t_cmd_list	*cmd;

	if (!cmds)
		return ;
	cmd = cmds;
	while (cmd)
	{
		if (cmd->argv
			&& cmd->argv[0]
			&& !ft_strchr(cmd->argv[0], '/')
			&& !is_builtin_function(cmd->argv[0])
			&& ft_strlen(cmd->argv[0]) > 0)
			search_executable(&(cmd->argv[0]), env);
		cmd = cmd->next;
	}
}
