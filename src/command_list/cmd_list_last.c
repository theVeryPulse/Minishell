/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_last.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:21:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 10:23:12 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_list.h"

t_cmd_list	*cmd_list_last(t_cmd_list *list)
{
	while (list->next)
		list = list->next;
	return (list);
}
