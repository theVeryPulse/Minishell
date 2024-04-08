/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer_part3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:19:01 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 16:52:14 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_list.h"
#include "libft.h"

static char	**list_to_string_array(t_list *list);
static void	free_all_nodes_leave_content(t_list **head);

void	add_this_cmd_to_list(t_cmd_list	**cmds, t_cmd_list *this_cmd,
		t_list **arguments, t_list **redirects)
{
	this_cmd->cmd_argv = list_to_string_array(*arguments);
	this_cmd->redirects = list_to_string_array(*redirects);
	free_all_nodes_leave_content(arguments);
	free_all_nodes_leave_content(redirects);
	cmd_list_append(cmds, this_cmd);
}

static char	**list_to_string_array(t_list *list)
{
	int		list_len;
	int		i;
	char	**string_array;

	if (!list)
	{
		return (NULL);
	}
	list_len = ft_lstsize(list);
	string_array = (char **)ft_calloc(list_len + 1, sizeof(char *));
	i = 0;
	while (i < list_len)
	{
		string_array[i] = (char *)list->content;
		list = list->next;
		i++;
	}
	return (string_array);
}

static void	free_all_nodes_leave_content(t_list **head)
{
	t_list	*node;
	t_list	*next_node;

	if (!head || !(*head))
		return ;
	node = *head;
	while (node)
	{
		next_node = node->next;
		free(node);
		node = next_node;
	}
	*head = NULL;
}
