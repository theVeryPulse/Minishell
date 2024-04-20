/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _stdin_stdout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 23:19:41 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 16:56:15 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_fd_action.h"
#include <unistd.h> /* STDIN_FILENO, STDOUT_FILENO */

/**
 * @brief Actions related to stdin and stdout: 
 *        `BACKUP`: back up stdin and stdout.
 *        `RESET_FROM_BACKUP`: reset stdin and stdout from backups.
 *        `CLOSE_BACKUP`: close backup file descriptors for stdin and stdout.
 *        `LOOKUP_STDIN_COPY`: look up the stdin back up file descriptor.
 * 
 * @param action 
 * @return int 
 */
extern int	_stdin_stdout(t_fd_action action)
{
	static int	stdin_copy = -1;
	static int	stdout_copy = -1;

	if (action == BACKUP)
	{
		stdin_copy = dup(STDIN_FILENO);
		stdout_copy = dup(STDOUT_FILENO);
	}
	else if (action == RESET_FROM_BACKUP)
	{
		dup2(stdin_copy, STDIN_FILENO);
		dup2(stdout_copy, STDOUT_FILENO);
	}
	else if (action == CLOSE_BACKUP)
	{
		close(stdin_copy);
		close(stdout_copy);
		stdin_copy = -1;
		stdout_copy = -1;
	}
	else if (action == LOOKUP_STDIN_COPY)
		return (stdin_copy);
	return (-1);
}
