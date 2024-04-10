/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update_name_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:28:18 by Philip            #+#    #+#             */
/*   Updated: 2024/04/10 01:33:32 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_env.h"
#include "libft.h"
#include <stdlib.h>

/**
 * @brief Updates the value of an existing environment variable or adds a new 
 *        environment variable.
 *
 * @param stack      A pointer to a pointer to the head of the linked list of 
 *                   environment variables.
 * @param name_value The name and value of the environment variable to update 
 *                   or add (in the form "name=value").
 */
void	env_update_name_value(t_env **stack, const char *name_value)
{
	t_env	*node;
	size_t	i;

	node = *stack;
	while (node)
	{
		i = 0;
		while (node->name_value[i] == name_value[i])
			i++;
		if (i > 0 && node->name_value[i - 1] == '=' && name_value[i - 1] == '=')
		{
			free(node->name_value);
			node->name_value = ft_strdup(name_value);
			return ;
		}
		node = node->next;
	}
	_add_to_env(stack, name_value);
}
