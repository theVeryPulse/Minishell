/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:49:25 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 15:14:14 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_env_append.h"
#include "t_env.h"
#include <stddef.h> /* NULL */

/**
 * @brief Creates a copy of the environment variables.
 * 
 * @param env The environment variables to copy.
 * @return `t_env*` A copy of the environment variables.
 */
extern t_env	*env_copy(t_env *env)
{
	t_env	*node;
	t_env	*copy;

	copy = NULL;
	node = env;
	while (node)
	{
		_env_append(&copy, node->name_value);
		node = node->next;
	}
	return (copy);
}
