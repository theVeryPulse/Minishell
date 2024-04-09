/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove_by_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:27:57 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 02:51:01 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stddef.h>
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
