/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:27:01 by Philip            #+#    #+#             */
/*   Updated: 2024/04/07 19:46:07 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment_variables.h"
#include "string_array.h"
#include "libft.h"
#include "free_and_null.h"

/* 
|command |options                                |
| ------ | ------------------------------------- |
| echo   | -n                                    |
| cd     | with only a relative or absolute path |
| pwd    | no options                            |
| export | no options                            |
| unset  | no options                            |
| env    | no options or arguments               |
| exit   | no options                            |
*/

/**
 * @brief Checks if a command is a built-in function
 * 
 * @param cmd Command to check
 * @return `bool`
 * @note `echo` `cd` `pwd` `export` `unset` `env` `exit`
 */
static bool	is_builtin_function(const char *cmd)
{
	return (ft_strncmp("cd", cmd, 10) == 0
			|| ft_strncmp("env", cmd, 10) == 0
			|| ft_strncmp("pwd", cmd, 10) == 0
			|| ft_strncmp("echo", cmd, 10) == 0
			|| ft_strncmp("exit", cmd, 10) == 0
			|| ft_strncmp("unset", cmd, 10) == 0
			|| ft_strncmp("export", cmd, 10) == 0);
}

void	search_executable(t_cmd_list *cmds, t_env *env)
{
	t_cmd_list	*cmd;
	char		*exe;
	char		*path_all;
	char		**paths;
	char		**path;

	if (!cmds)
		return ;
	path_all = env_get_value_by_name(env, "PATH");
	paths = ft_split(path_all, ':');
	free_and_null((void **)&path_all);
	cmd = cmds;
	while (cmd)
	{
		if (ft_strchr(cmd->cmd_argv[0], '/')
			|| is_builtin_function(cmd->cmd_argv[0]))
		{
			cmd = cmd->next;
			continue ;
		}
		path = paths;
		while (path && *path)
		{
			exe = ft_format_string("%s/%s", *path, cmd->cmd_argv[0]);
			if (access(exe, F_OK) == 0)
			{
				free_and_null((void **)&(cmd->cmd_argv[0]));
				cmd->cmd_argv[0] = exe;
				break ;
			}
			free_and_null((void **)&exe);
			path++;
		}
		cmd = cmd->next;
	}
	free_string_array_and_null(&paths);
}
