/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_list_add_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:10:57 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 10:15:08 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char_list.h"
#include "libft.h"

static t_char_list	*char_list_last_node(t_char_list *list);

void	char_list_add_char(t_char_list **list, char c)
{
	t_char_list	*new_node;

	new_node = (t_char_list *)ft_calloc(1, sizeof(t_char_list));
	new_node->c = c;
	if (!(*list))
		*list = new_node;
	else
		char_list_last_node(*list)->next = new_node;
}

static t_char_list	*char_list_last_node(t_char_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);	
}
