/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:49:25 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 01:11:11 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_env.h"
#include "t_env.h"
#include <stddef.h>

static void	_add_to_stack(t_env **copy, t_env *node);

t_env	*env_copy(t_env *env)
{
	t_env	*node;
	t_env	*copy;

	copy = NULL;
	node = env;
	_add_to_stack(&copy, node);
	return (copy);
}

static void	_add_to_stack(t_env **copy, t_env *node)
{
	if (node->next == NULL)
	{
		_add_to_env(copy, node->name_value);
	}
	else
	{
		_add_to_stack(copy, node->next);
		_add_to_env(copy, node->name_value);
	}
}
