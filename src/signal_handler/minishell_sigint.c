/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_sigint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:02:23 by Philip            #+#    #+#             */
/*   Updated: 2024/04/17 13:13:32 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exit_status.h"
#include "../minishell/minishell.h"
#include "../environment_variables/env.h"
#include <unistd.h>
#include <readline/readline.h>

extern void	minishell_sigint(int signal)
{
	signal++;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	rl_done = 1;
	env_update_exit_status(&(minishell()->env), SIGINT_EXIT_STATUS);
	minishell()->received_signal = RECEIVED_SIGINT;
}
