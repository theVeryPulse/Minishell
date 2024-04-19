/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fd_action.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:39:06 by Philip            #+#    #+#             */
/*   Updated: 2024/04/19 21:14:06 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_FD_ACTION_H
# define T_FD_ACTION_H

typedef enum e_fd_action
{
	BACKUP,
	RESET_FROM_BACKUP,
	CLOSE_BACKUP,
	LOOKUP_STDIN
}	t_fd_action;

#endif