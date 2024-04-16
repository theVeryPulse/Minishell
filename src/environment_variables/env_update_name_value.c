/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update_name_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:28:18 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 01:17:14 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
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

	if (ft_strncmp(name_value, "?=", 2) != 0
		&& !is_valid_identifier(name_value))
		return ;
	node = *stack;
	while (node)
	{
		i = 0;
		while (node->name_value[i]
			&& node->name_value[i] != '='
			&& node->name_value[i] == name_value[i])
			i++;
		if (i > 0 && node->name_value[i] == '=' && name_value[i] == '=')
		{
			free(node->name_value);
			node->name_value = ft_strdup(name_value);
			return ;
		}
		node = node->next;
	}
	_add_to_env(stack, name_value);
}
