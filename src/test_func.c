/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 23:16:06 by Philip            #+#    #+#             */
/*   Updated: 2024/04/03 23:36:22 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

void	print_and_free_cmds(t_cmd_list *cmds)
{
	int		cmd_argc;
	int		argv_idx;
	t_list	*node;
	int		redirect_count;
	int		redirect_idx;
	t_cmd_list	*cmd;
	t_cmd_list	*next_cmd;

	cmd = cmds;
	while (cmd)
	{
		next_cmd = cmd->next;
		printf("\n===Command===\n");
		printf("---Arguments---\n");
		argv_idx = 0;
		while (cmd->cmd_argv && cmd->cmd_argv[argv_idx])
		{
			printf("%d: %s\n", argv_idx, cmd->cmd_argv[argv_idx]);
			argv_idx++;
		}
		printf("---Redirects---\n");
		redirect_idx = 0;
		while (cmd->redirects && cmd->redirects[redirect_idx])
		{
			printf("%d: %s\n", redirect_idx, cmd->redirects[redirect_idx]);
			redirect_idx++;
		}
		cmd = next_cmd;
	}
	cmd_list_free(&cmds);
}