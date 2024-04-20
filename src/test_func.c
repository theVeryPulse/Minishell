/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 23:16:06 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 17:22:53 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "module_functions.h"
#include "libft.h"
#include <stdio.h>

void	print_cmds(t_cmd_list *cmds)
{
	int			argv_idx;
	int			redirect_idx;
	t_cmd_list	*cmd;

	cmd = cmds;
	while (cmd)
	{
		printf("Command\n");
		printf("  Arguments\n");
		argv_idx = 0;
		while (cmd->argv && cmd->argv[argv_idx])
		{
			printf("    %d: %s\n", argv_idx, cmd->argv[argv_idx]);
			argv_idx++;
		}
		printf("  Redirects\n");
		redirect_idx = 0;
		while (cmd->redirects && cmd->redirects[redirect_idx])
		{
			printf("    %d: %s\n", redirect_idx, cmd->redirects[redirect_idx]);
			redirect_idx++;
		}
		cmd = cmd->next;
	}
}
