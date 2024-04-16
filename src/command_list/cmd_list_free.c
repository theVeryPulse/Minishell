/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:21:52 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 02:12:51 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cmd_list.h"
#include "../string_array.h"
#include <stdlib.h>

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
		free_string_array_and_null(&node->argv);
		free_string_array_and_null(&node->redirects);
		free(node);
		node = next_node;
	}
	*list = NULL;
}
