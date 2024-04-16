/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_sigquit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:11:03 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 21:30:41 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include "../minishell/minishell.h"
#include "../free/free.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

extern void	child_sigquit(int signal)
{
	signal++;
	free_cmds_env_pipes_rl_clear_history((t_to_free){.cmds = minishell()->cmds,
		.env = minishell()->env});
	exit(SIGQUIT_EXIT_STATUS);
}
