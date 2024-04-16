/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:03:16 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 22:35:22 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

extern void	minishell_sigint(int signal);

extern void	waiting_child_sigint(int signal);
extern void	waiting_child_sigquit(int signal);

extern void	child_sigint(int signal);
extern void	child_sigquit(int signal);

extern void	heredoc_sigint(int signal);

#endif
 