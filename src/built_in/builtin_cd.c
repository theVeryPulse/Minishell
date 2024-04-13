/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuleung <chuleung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 13:03:40 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/13 23:43:15 by chuleung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environment_variables/env.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

int	_check_cd_dir(char *name_value, int *exit_status)
{
	int	check;
	
	check = 0;
	if (access(name_value, F_OK) != 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: no such file or directory: "
				"`%s'\n", name_value);
		check = -1;
		*exit_status = 1;
	}
	else 
	{
		if (access(name_value, R_OK) != 0)
		{
			ft_dprintf(STDERR_FILENO, "minishell: cd: permission denied: "
				"`%s'\n", name_value);
			check = -1;
			*exit_status = 1;
		}
	}
	return (check);
}

/**
 * 
 * input:
 * cd
 * cd not_exist
 * cd no_permission_folder V
 * cd {a folder that exists and user has permission} another_arg V
 * 
*/
int builtin_cd(t_env **env, char **cmd_argv)
{
	int     exit_status;
	int     error;
	char	*name_value;

	env += 1;
	exit_status = 0;
	if (!cmd_argv || !(cmd_argv[1]))
		return (exit_status);
	name_value = cmd_argv[1];
	}
	if((_check_cd_dir(name_value, &exit_status) != 0))
		return (exit_status);
	error = chdir(name_value);
	if (error == -1)
	{
		perror("chdir");
		exit_status = 1;
	}
	return (exit_status);
}
