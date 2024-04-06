/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 23:13:02 by Philip            #+#    #+#             */
/*   Updated: 2024/04/06 02:02:48 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_list.h"
#include "libft.h"
#include <stddef.h>

static void	free_string_array(char **string_array);

t_cmd_list	*cmd_list_new(void)
{
	return ((t_cmd_list *)ft_calloc(1, sizeof(t_cmd_list)));
}

t_cmd_list	*cmd_list_last(t_cmd_list *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

void	cmd_list_append(t_cmd_list **list, t_cmd_list *node)
{
	if (!list)
		return ;
	if (!(*list))
		*list = node;
	else
		cmd_list_last(*list)->next = node;
}

void	cmd_list_free(t_cmd_list **list)
{
	t_cmd_list	*node;
	t_cmd_list	*next_node;

	if (!list || !(*list))
		return ;
	node = *list;
	while (node)
	{
		next_node = node->next;
		free_string_array(node->cmd_argv);
		free_string_array(node->redirects);
		free(node->cmd_argv);
		free(node->redirects);
		free(node);
		node = next_node;
	}
	*list = NULL;
}

static void	free_string_array(char **string_array)
{
	while (string_array && *string_array)
	{
		free(*string_array);
		string_array++;
	}
}
