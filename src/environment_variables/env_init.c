/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:27:19 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 02:49:43 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" /* env_update_name_value */
#include <unistd.h> /* __environ, NULL */

/**
 * @brief Initializes the environment variables from `__environ`.
 *
 * @param env Pointer to the pointer to environment variables.
 */
extern void	env_init(t_env **env)
{
	char	**env_var;

	*env = NULL;
	env_var = __environ;
	while (env_var && *env_var)
	{
		env_update_name_value(env, *env_var);
		env_var++;
	}
	env_update_name_value(env, "?=0");
}
