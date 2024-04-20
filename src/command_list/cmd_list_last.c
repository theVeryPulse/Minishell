/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_last.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:21:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 14:55:06 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cmd_list.h"

/**
 * @brief Finds the last node of a command list and return its address
 * 
 * @param list The command list to find last node.
 * @return `t_cmd_list*` The last node of the command list.
 */
extern t_cmd_list	*cmd_list_last(t_cmd_list *list)
{
	while (list->next)
		list = list->next;
	return (list);
}
