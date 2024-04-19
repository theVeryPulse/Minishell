/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _stdin_stdout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 23:19:41 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 00:42:25 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_fd_action.h"
#include <unistd.h> /* STDIN_FILENO, STDOUT_FILENO */

int	_stdin_stdout(t_fd_action action)
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
	else if (action == LOOKUP_STDIN)
		return (stdin_copy);
	return (-1);
}
