/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_child_sigint.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:20:33 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 22:26:15 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell/minishell.h"
#include "../environment_variables/env.h"
#include "exit_status.h"
#include "libft.h"
#include <unistd.h>
#include <readline/readline.h>

extern void	waiting_child_sigint(int signal)
{
	signal++;
	minishell()->received_signal = RECEIVED_SIGINT;
	minishell()->exit_status = SIGINT_EXIT_STATUS;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
}
