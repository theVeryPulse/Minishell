/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuleung <chuleung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 21:15:26 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/15 17:33:51 by chuleung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environment_variables/env.h"
#include "../environment_variables/_env.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int		_unset_arg_check(char **cmd_argv, int *exit_status,
	int *nbr_of_items)
{
	if(cmd_argv[1] == NULL)
	{
		ft_dprintf(STDERR_FILENO, "minishell: unset: not enough arguments");
		*exit_status = 1;
		return (1);
	}
	while (cmd_argv[*nbr_of_items])
		(*nbr_of_items)++;
	return (0);
}

void	builtin_unset(char **cmd_argv, t_env **env)
{
	int	i;
	int	exit_status;
	int	nbr_of_items;

	i = 1;
	exit_status = 0;
	nbr_of_items = 0;
	if (_unset_arg_check(cmd_argv, &exit_status, &nbr_of_items))
		exit (exit_status);
	if (i < nbr_of_items)
	{
		env_remove_by_name(env, cmd_argv[i]);
		i++;
	}
	exit (exit_status);
}

// void builtin_export(t_env *env, char *cmd_argv)
// {
//     if (ft_unset(cmd_argv[0], "unset", 6))
//         exit (1);
//     env_remove_by_name(&env, cmd_argv[1]);
// }
