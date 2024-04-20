/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_sigquit_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:42:32 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 00:25:45 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell/minishell.h"
#include "../environment_variables/env.h" /* env_update_exit_status */
#include "../exit_status.h"
#include "t_signal_status.h"
#include "libft.h" /* ft_dprintf */
#include <signal.h> /* signal */
#include <unistd.h> /* STDERR_FILENO */
#include <readline/readline.h> /* rl_on_new_line, rl_done, etc. */

extern void	sigint_sigquit_handler(t_signal_status status);
static void	waiting_child_sigint(int signal);
static void	waiting_child_sigquit(int signal);
static void	minishell_sigint(int signal);
static void	heredoc_sigint(int signal);

extern void	sigint_sigquit_handler(t_signal_status status)
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

static void	waiting_child_sigquit(int signal)
{
	signal++;
	minishell()->received_signal = RECEIVED_SIGQUIT;
	minishell()->exit_status = SIGQUIT_EXIT_STATUS;
	ft_dprintf(STDERR_FILENO, "Quit (core dumped)\n");
	rl_on_new_line();
}

static void	waiting_child_sigint(int signal)
{
	signal++;
	minishell()->received_signal = RECEIVED_SIGINT;
	minishell()->exit_status = SIGINT_EXIT_STATUS;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
}

static void	minishell_sigint(int signal)
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

static void	heredoc_sigint(int signal)
{
	signal++;
	rl_done = 1;
	env_update_exit_status(&(minishell()->env), SIGINT_EXIT_STATUS);
	minishell()->received_signal = RECEIVED_SIGINT;
}
