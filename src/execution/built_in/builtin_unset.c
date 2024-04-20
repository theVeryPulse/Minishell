/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 21:15:26 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/20 14:11:48 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../environment_variables/env.h" /* env_remove_by_name */

/**
 * @brief Removes environment variables.
 * 
 * @param argv Array of the arguments, first argument being "unset"
 * @param env Pointer to the pointer to the environment variables.
 * @return Always returns 0.
 */
extern int	builtin_unset(char **argv, t_env **env)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		env_remove_by_name(env, argv[i]);
		i++;
	}
	return (0);
}
