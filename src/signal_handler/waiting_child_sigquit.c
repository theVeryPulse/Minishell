/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_child_sigquit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:07:22 by Philip            #+#    #+#             */
/*   Updated: 2024/04/17 13:13:48 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell/minishell.h"
#include "../environment_variables/env.h"
#include "../exit_status.h"
#include "libft.h"
#include <unistd.h>
#include <readline/readline.h>

extern void	waiting_child_sigquit(int signal)
{
	signal++;
	minishell()->received_signal = RECEIVED_SIGQUIT;
	minishell()->exit_status = SIGQUIT_EXIT_STATUS;
	ft_dprintf(STDERR_FILENO, "Quit (core dumped)\n");
	rl_on_new_line();
}
