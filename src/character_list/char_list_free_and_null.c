/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_list_free_and_null.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:09:41 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 14:28:59 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_char_list.h"
#include <stdlib.h> /* free, NULL */

/**
 * @brief Frees the memory taken by the character list and reset pointer to
 *        NULL.
 * 
 * @param list Pointer to the pointer to the character list.
 */
void	char_list_free_and_null(t_char_list **list)
{
	t_char_list	*node;
	t_char_list	*next;

	if (!list || !(*list))
		return ;
	node = *list;
	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
	*list = NULL;
}
