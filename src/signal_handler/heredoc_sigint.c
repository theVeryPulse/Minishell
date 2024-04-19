/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sigint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:30:55 by Philip            #+#    #+#             */
/*   Updated: 2024/04/19 19:09:50 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exit_status.h"
#include "../minishell/minishell.h"
#include "../environment_variables/env.h"
#include <unistd.h>
#include <readline/readline.h>

extern void	heredoc_sigint(int signal)
{
	signal++;
	rl_done = 1;
	env_update_exit_status(&(minishell()->env), SIGINT_EXIT_STATUS);
	minishell()->received_signal = RECEIVED_SIGINT;
}
