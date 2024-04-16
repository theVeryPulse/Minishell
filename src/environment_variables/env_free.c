/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:28:59 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 01:48:50 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_env.h"
#include <stdlib.h>

/**
 * @brief Frees memory of the entire linked list for environment variables.
 *        Resets pointer to NULL.
 *
 * @param list A pointer to the pointer to the head of the linked list of
 *             environment variables.
 */
void	env_free(t_env **list)
{
	t_env	*node;
	t_env	*next_node;

	if (!list || !(*list))
		return ;
	node = *list;
	while (node)
	{
		next_node = node->next;
		free(node->name_value);
		free(node);
		node = next_node;
	}
	*list = NULL;
}
