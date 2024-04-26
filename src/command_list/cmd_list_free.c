/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:21:52 by Philip            #+#    #+#             */
/*   Updated: 2024/04/26 01:03:46 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cmd_list.h"
#include "../free/free.h"
#include <stdlib.h>
#include <unistd.h> /* unlink */

/**
 * @brief Frees the command list and resets the pointer to NULL. Also unlinks
 *        temporary heredoc files if any.
 * 
 * @param list Pointer to the pointer to the command list.
 */
extern void	cmd_list_free(t_cmd_list **list)
{
	t_cmd_list	*node;
	t_cmd_list	*next_node;

	if (!list || !(*list))
		return ;
	node = *list;
	while (node)
	{
		next_node = node->next;
		free_string_array_and_null(&node->argv);
		free_string_array_and_null(&node->redirects);
		unlink(node->heredoc);
		free(node->heredoc);
		free(node);
		node = next_node;
	}
	*list = NULL;
}
