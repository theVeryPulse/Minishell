/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_list_free_and_null.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:09:41 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 10:14:31 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char_list.h"
#include <stdlib.h>
#include <stddef.h>

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
