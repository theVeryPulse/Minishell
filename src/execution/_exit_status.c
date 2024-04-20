/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 02:25:57 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 17:01:41 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell/minishell.h"
#include <sys/types.h> /* pid_t */
#include <wait.h> /* waitpid */

/**
 * @brief Returns the exit status of target process.
 * 
 * @param id Process from which to get exit status.
 * @return `int` Exit status.
 */
extern int	_exit_status(pid_t id)
{
	int	wstatus;
	int	exit_status;

	exit_status = 0;
	waitpid(id, &wstatus, 0);
	if (WIFEXITED(wstatus))
		exit_status = WEXITSTATUS(wstatus);
	if (minishell()->received_signal != NONE)
		exit_status = minishell()->exit_status;
	return (exit_status);
}
