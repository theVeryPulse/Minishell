/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lexical_analyzer.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:54:34 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 02:11:58 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LEXICAL_ANALYZER_H
# define _LEXICAL_ANALYZER_H

# include "../cmd_list.h"
# include "libft.h"

void	_add_this_cmd_to_list(t_cmd_list **cmds, t_cmd_list *this_cmd,
			t_list **arguments, t_list **redirects);
void	_add_argument_and_update_i(t_list **arguments, const char *line,
			size_t *i);
void	_add_redirect_and_update_i(t_list **redirects, const char *line,
			size_t *i);
char	*_get_next_word_and_update_i(const char *line, size_t *i);

#endif