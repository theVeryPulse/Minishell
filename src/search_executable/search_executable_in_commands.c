/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_executable_in_commands.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:27:01 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 16:49:03 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paths.h"
#include "search_executable.h"
#include "../environment_variables/env.h"
#include "../execution/built_in/built_in.h"
#include "../free/free.h"
#include "libft.h"
#include <stdbool.h>
#include <unistd.h>

/**
 * @brief Searches for executable files in the directories specified by the PATH
 *        environment variable. If executable is found, the file path will
 *        replace the original argument. Skips built-in functions.
 *
 * @param cmds A pointer to the head of the linked list of command nodes.
 * @param env  A pointer to the head of the linked list of environment variables.
 */
void	search_executable_in_commands(t_cmd_list *cmds, t_env *env)
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
