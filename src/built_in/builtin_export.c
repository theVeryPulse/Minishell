/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:43:07 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/14 21:45:28 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environment_variables/env.h"
#include "../character_checks/character_checks.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

/**
 * @brief Updates environment variables or exports new ones.
 * 
 * @param env A pointer to the pointer to the stack of environment variables.
 * @param cmd_argv An array of strings containing the command arguments.
 * @return The exit status of the function, 0 if successful, 1 otherwise.
 */
int	builtin_export(t_env **env, char **cmd_argv)
{
	int		i;
	char	*name_value;
	int		exit_status;

	exit_status = 0;
	if (!cmd_argv || !(cmd_argv[1]))
		return (exit_status);
	i = 1;
	while (cmd_argv[i])
	{
		name_value = cmd_argv[i];
		if (!is_valid_identifier(name_value))
		{
			ft_dprintf(STDERR_FILENO, "minishell: export: `%s': not a valid "
				"identifier\n", name_value);
			exit_status = 1;
		}
		else if (ft_strchr(name_value, '='))
			env_update_name_value(env, name_value);
		i++;
	}
	return (exit_status);
}
