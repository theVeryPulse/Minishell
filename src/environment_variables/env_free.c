/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:28:59 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 15:11:08 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_env.h"
#include <stdlib.h> /* free */

/**
 * @brief Frees memory of environment variables. Resets pointer to NULL.
 *
 * @param list Pointer to the pointer to the environment variables.
 */
extern void	env_free(t_env **list)
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
