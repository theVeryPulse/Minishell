/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _add_this_cmd_to_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:53:25 by Philip            #+#    #+#             */
/*   Updated: 2024/04/27 18:11:29 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../command_list/cmd_list.h"
#include "libft.h"
#include <stdlib.h>

extern void	_add_this_cmd_to_list(t_cmd_list **cmds, t_cmd_list *this_cmd,
				t_list **arguments, t_list **redirects);
static char	**_list_to_string_array(t_list *list);
static void	_free_all_nodes_leave_content(t_list **head);
static int	_heredoc_index(void);

/**
 * @brief Add a command tto the list with current arguments and redirects, then
 *        free the memory for arguments and redirects.
 * 
 * @param cmds Pointer to the pointer to the command list.
 * @param this_cmd Command node to add add to list.
 * @param arguments List of arguments to be converted to string arrays.
 * @param redirects List of redirects to be converted to string arrays.
 */
extern void	_add_this_cmd_to_list(t_cmd_list **cmds, t_cmd_list *this_cmd,
		t_list **arguments, t_list **redirects)
{
	char	*heredoc;

	heredoc = ft_format_string(".heredoc%d", _heredoc_index());
	this_cmd->argv = _list_to_string_array(*arguments);
	this_cmd->redirects = _list_to_string_array(*redirects);
	this_cmd->heredoc = heredoc;
	_free_all_nodes_leave_content(arguments);
	_free_all_nodes_leave_content(redirects);
	cmd_list_append(cmds, this_cmd);
}

static char	**_list_to_string_array(t_list *list)
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

static void	_free_all_nodes_leave_content(t_list **head)
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

static int	_heredoc_index(void)
{
	static int	index;

	return (index++);
}
