/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _add_redirect_and_update_i.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:56:57 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 02:09:25 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_lexical_analyzer.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	_add_redirect_and_update_i(
			t_list **redirects, const char *line, size_t *i)
{
	char	*redirect_symbols;
	char	*word;
	char	*redirect_str;
	size_t	i_copy;

	i_copy = *i;
	if (line[i_copy + 1] == line[i_copy])
		redirect_symbols = ft_strndup(&line[i_copy++], 2);
	else
		redirect_symbols = ft_strndup(&line[i_copy], 1);
	i_copy++;
	while (ft_isspace(line[i_copy]))
		i_copy++;
	word = _get_next_word_and_update_i(line, &i_copy);
	redirect_str = ft_strjoin(redirect_symbols, word);
	ft_lstadd_back(redirects, ft_lstnew((void *)redirect_str));
	free(redirect_symbols);
	free(word);
	*i = i_copy;
	printf("\"%s\" added to list\n", (char *)ft_lstlast(*redirects)->content); /* Test */
}
