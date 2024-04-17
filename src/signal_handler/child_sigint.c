/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_sigint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:11:03 by Philip            #+#    #+#             */
/*   Updated: 2024/04/17 13:13:15 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exit_status.h"
#include "../minishell/minishell.h"
#include "../free/free.h"
#include <stdlib.h>

extern void	child_sigint(int signal)
{
	signal++;
	free_cmds_env_pipes_rl_clear_history((t_to_free){.cmds = minishell()->cmds,
		.env = minishell()->env});
	exit(SIGINT_EXIT_STATUS);
}
