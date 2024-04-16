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

#include "env.h"
#include <stddef.h>
#include <unistd.h>

/**
 * @brief Initializes an environment variable linked list with the current 
 *        environment variables.
 *
 * @param stack A pointer to the pointer to the head of the linked list of 
 *              environment variables.
 */
void	env_init(t_env **env)
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
