/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:27:01 by Philip            #+#    #+#             */
/*   Updated: 2024/04/15 12:59:46 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "search_executable.h"
#include "minishell.h"
#include "environment_variables/env.h"
#include "string_array.h"
#include "is_builtin_function.h"
#include "libft.h"
#include "free_and_null.h"
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
void	search_executable(t_cmd_list *cmds, t_env *env)
{
	t_cmd_list	*cmd;
	char		*path_all;
	char		**paths;

	if (!cmds)
		return ;
	path_all = env_get_value_by_name(env, "PATH");
	paths = ft_split(path_all, ':');
	free_and_null((void **)&path_all);
	cmd = cmds;
	while (cmd)
	{
		if (cmd->cmd_argv
			&& !ft_strchr(cmd->cmd_argv[0], '/')
			&& !is_builtin_function(cmd->cmd_argv[0])
			&& ft_strlen(cmd->cmd_argv[0]) > 0)
		{
			// _try_find_executable(cmd, paths);
			search_exec_and_replace_arg(&(cmd->cmd_argv[0]), paths);
		}
		cmd = cmd->next;
	}
	free_string_array_and_null(&paths);
}
