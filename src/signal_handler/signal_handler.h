/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:03:16 by Philip            #+#    #+#             */
/*   Updated: 2024/04/19 21:18:03 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

typedef enum e_signal_status
{
	WAITING_CHILD,
	HEREDOC,
	DEFAULT,
	MINISHELL
}	t_signal_status;

void		sigint_sigquit_handler(t_signal_status status);

/* Input stage */

extern void	minishell_sigint(int signal);

/* Waiting child execution stage */

extern void	waiting_child_sigint(int signal);
extern void	waiting_child_sigquit(int signal);

/* Child process signal handling */

extern void	child_sigint(int signal);
extern void	child_sigquit(int signal);

/* Heredoc status */

extern void	heredoc_sigint(int signal);

#endif
