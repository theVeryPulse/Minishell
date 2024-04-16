/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:04:29 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 17:58:31 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./t_minishell.h"

extern void			minishell_init(void);
extern t_minishell	*minishell(void);
extern void			minishell_free(void);

#endif