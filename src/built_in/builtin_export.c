/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:43:07 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/12 23:58:33 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environment_variables/env.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

/**
 * @brief 
 * 
 * @param identifier 
 * @return true 
 * @note - If there is a '?' before '=', it is invalid identifier
 *       - If there is not a '=' in the identifier, it is valid but has no 
 *         effect
 * 
 */ 
bool	_not_valid_identifier(char *identifier)
{
	size_t	i;

	i = 0;
	while (identifier[i])
	{
		/* Try skipping the name */
		while (identifier[i] && identifier[i] != '=') /* Name contains '?' */
		{
			if (identifier[i] == '?')
				return (true);
			i++;
		}
		/* If there is no name before '=', identifier is invalid */
		if (i == 0)
			return (true);
		
		i++;
	}
	return (false);
}

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
			ft_dprintf(STDERR_FILENO, "minishell: export: `%s': not a valid"
				"identifier\n", name_value);
			exit_status = 1;
		}
		else if (ft_strchr(name_value, '='))
		{
			env_update_name_value(env, name_value);
		}
		i++;
	}
	return (exit_status);
}

/*
void export_var(char *name, char *value)
{
    int     id;
    char    *new_env[] = env_update_name_value(env, )
    char    *new_argv[] = {"/bin/bash", "-c", "echo $MY_VARIABLE", NULL};

    if (fork() == 0)
    {
        execve("/bin/echo", new_argv, new_env);
        exit(EXIT_FAILURE);
    } 
    else 
        wait(NULL);
}
*/
