/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fd_action.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:39:06 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 16:55:58 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_FD_ACTION_H
# define T_FD_ACTION_H

typedef enum e_fd_action
{
	/* back up STDIN_FILENO and STDOUT_FILENO */
	BACKUP,
	/* reset STDIN_FILENO and STDOUT_FILENO from backups */
	RESET_FROM_BACKUP,
	/* close backups of STDIN_FILENO and STDOUT_FILENO */
	CLOSE_BACKUP,
	/* returns backup of STDIN_FILENO */
	LOOKUP_STDIN_COPY
}	t_fd_action;

#endif