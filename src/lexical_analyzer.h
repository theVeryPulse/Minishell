/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:56:16 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 16:59:20 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICAL_ANALYZER_H
# define LEXICAL_ANALYZER_H
# include "cmd_list.h"
# include "libft.h"

void	add_redirect_and_update_i(t_list **redirects, const char *line,
			size_t *i);
void	add_argument_and_update_i(t_list **arguments, const char *line,
			size_t *i);
void	add_this_cmd_to_list(t_cmd_list	**cmds, t_cmd_list *this_cmd,
			t_list **arguments, t_list **redirects);

#endif