/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 21:15:26 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/16 16:34:13 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environment_variables/env.h"

/**
 * @brief Removes environment variables.
 * 
 * @param argv String array of the arguments, first one being "unset"
 * @param env A pointer to the pointer to the environment variables.
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
