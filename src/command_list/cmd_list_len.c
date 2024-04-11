/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 01:44:46 by Philip            #+#    #+#             */
/*   Updated: 2024/04/11 02:07:25 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_list.h"

/**
 * @brief Get the length of the command list.
 * 
 * @param cmds Pointer to the head of the command list.
 * @return `int` The number of elements in the command list.
 */
int	cmd_list_len(t_cmd_list *cmds)
{
	int			len;
	t_cmd_list	*cmd;

	cmd = cmds;
	len = 0;
	while (cmd)
	{
		len++;
		cmd = cmd->next;
	}
	return (len);
}