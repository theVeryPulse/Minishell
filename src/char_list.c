/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:34:06 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 17:02:45 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char_list.h"
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

static t_char_list	*char_list_last_node(t_char_list *list);

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

char	*char_list_to_str(t_char_list *list)
{
	size_t	len;
	size_t	i;
	t_char_list	*node;
	char	*str;

	if (!list)
		return (NULL);
	node = list;
	len = 0;
	while (node)
	{
		node = node->next;
		len++;
	}
	str = (char *)ft_calloc(len + 1, sizeof(char));
	node = list;
	i = 0;
	while (node)
	{
		str[i++] = node->c;
		node = node->next;
	}
	return (str);
}

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

void	char_list_add_str(t_char_list **list, char *str)
{
	while (*str)
	{
		char_list_add_char(list, *str);
		str++;
	}
}

static t_char_list	*char_list_last_node(t_char_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);	
}
