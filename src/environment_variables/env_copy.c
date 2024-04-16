/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:49:25 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 01:53:24 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_env.h"
#include "t_env.h"
#include <stddef.h>

t_env	*env_copy(t_env *env)
{
	t_env	*node;
	t_env	*copy;

	copy = NULL;
	node = env;
	while (node)
	{
		_add_to_env(&copy, node->name_value);
		node = node->next;
	}
	return (copy);
}
