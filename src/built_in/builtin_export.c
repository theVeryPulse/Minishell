/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:43:07 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/13 02:11:04 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environment_variables/env.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

static bool	_not_valid_identifier(char *identifier);

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
	env_update_name_value(env, cmd_argv[1]);
	i = 1;
	while (cmd_argv[i])
	{
		name_value = cmd_argv[i];
		if (_not_valid_identifier(name_value))
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

/**
 * @brief Checks if an argument is not a valid identifier, in the format of
 *        `name=value`
 * 
 * @param identifier Argument to check
 * @return `true` if identifier is invalid, else `false` 
 * @note 
 * Invalid identifiers include:
 * - a '?' anywhere before '=', e.g. "?=1"
 * - a '$' 
 * - no name before '=', e.g. "==3"
 * 
 * Special case:
 * - when there is no '=' in the identifier, it is valid but has no effect
 */
static bool	_not_valid_identifier(char *identifier)
{
	size_t	i;

	i = 0;
	while (identifier[i])
	{
		while (identifier[i] && identifier[i] != '=')
		{
			if (identifier[i] == '?')
				return (true);
			i++;
		}
		if (i == 0)
			return (true);
		i++;
	}
	return (false);
}
