/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:42:32 by Philip            #+#    #+#             */
/*   Updated: 2024/04/19 19:54:48 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"
#include <signal.h>

void	sigint_sigquit_handler(t_signal_status status)
{
	if (status == WAITING_CHILD)
	{
		signal(SIGQUIT, waiting_child_sigquit);
		signal(SIGINT, waiting_child_sigint);
	}
	else if (status == DEFAULT)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	else if (status == MINISHELL)
	{
		signal(SIGINT, minishell_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == HEREDOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, heredoc_sigint);
	}
}
