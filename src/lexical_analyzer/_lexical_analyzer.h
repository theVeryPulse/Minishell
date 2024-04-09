/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lexical_analyzer.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:54:34 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 20:42:39 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LEXICAL_ANALYZER_H
# define _LEXICAL_ANALYZER_H

# include "../command_list/cmd_list.h"
# include "libft.h"

void	_add_this_cmd_to_list(t_cmd_list **cmds, t_cmd_list *this_cmd,
			t_list **arguments, t_list **redirects);
char	*_get_next_word_and_update_i(const char *line, size_t *i);

#endif