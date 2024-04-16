/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove_by_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:27:57 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 01:12:02 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_env.h"
#include <stdlib.h>

/*
3 cases of removing a node:

start: (node == *stack)
A->B->C
B->C->NULL

middle: prev->next = node->next;
A->B->C->NULL
A->C->NULL

end: prev->next = node->next;
A->B->C->NULL
A->B->NULL

 */

/**
 * @brief Removes an environment variable by its name from a linked list.
 *
 * @param stack A pointer to a pointer to the head of the linked list of 
 *              environment variables.
 * @param name  The name of the environment variable to remove.
 */
void	env_remove_by_name(t_env **stack, const char *name)
{
	t_env	*node;
	t_env	*prev;
	size_t	i;

	node = *stack;
	while (node)
	{
		i = 0;
		while (node->name_value[i] == name[i])
			i++;
		if (node->name_value[i] == '=' && name[i] == '\0')
		{
			if (node == *stack)
				*stack = node->next;
			else
				prev->next = node->next;
			return (free(node->name_value), free(node));
		}
		prev = node;
		node = node->next;
	}
}
