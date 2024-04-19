/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_signal_status.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:24:57 by Philip            #+#    #+#             */
/*   Updated: 2024/04/19 22:25:39 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SIGNAL_STATUS_H
# define T_SIGNAL_STATUS_H

typedef enum e_signal_status
{
	WAITING_CHILD,
	HEREDOC,
	DEFAULT,
	MINISHELL
}	t_signal_status;

#endif