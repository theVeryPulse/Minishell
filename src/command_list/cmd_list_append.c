/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:21:45 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 10:23:28 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_list.h"

void	cmd_list_append(t_cmd_list **list, t_cmd_list *node)
{
	if (!list)
		return ;
	if (!(*list))
		*list = node;
	else
		cmd_list_last(*list)->next = node;
}
