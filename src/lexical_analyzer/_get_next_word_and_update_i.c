/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _get_next_word_and_update_i.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:49:41 by Philip            #+#    #+#             */
/*   Updated: 2024/04/14 10:54:57 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../character_checks/character_checks.h"
#include "libft.h"

static void	_set_end_idx_to_close_quote(const char *line, size_t *end_idx);
static void	_set_end_idx_to_word_end(const char *line, size_t *end_idx);

char	*_get_next_word_and_update_i(const char *line, size_t *i)
{
	size_t	i_copy;
	char	*word;
	size_t	end_idx;

	i_copy = *i;
	if (is_metacharacter(line[i_copy]))
		return (ft_calloc(1, sizeof(char)));
	while (ft_isspace(line[i_copy]))
		i_copy++;
	end_idx = i_copy;
	while (line[end_idx] && !is_metacharacter(line[end_idx]))
	{
		if (is_quotation_mark(line[end_idx]))
			_set_end_idx_to_close_quote(line, &end_idx);
		else
			_set_end_idx_to_word_end(line, &end_idx);
	}
	word = ft_strndup(&line[i_copy], end_idx - i_copy);
	*i = end_idx;
	return (word);
}

static void	_set_end_idx_to_close_quote(const char *line, size_t *end_idx)
{
	char	*close_quote;
	size_t	end_idx_copy;

	end_idx_copy = *end_idx;
	close_quote = ft_strchr(&line[end_idx_copy + 1], line[end_idx_copy]);
	if (close_quote)
		end_idx_copy = close_quote - line + 1;
	else
	{
		while (line[end_idx_copy])
			end_idx_copy++;
	}
	*end_idx = end_idx_copy;
}

static void	_set_end_idx_to_word_end(const char *line, size_t *end_idx)
{
	size_t	end_idx_copy;

	end_idx_copy = *end_idx;
	while (line[end_idx_copy]
		&& !is_metacharacter(line[end_idx_copy])
		&& !is_quotation_mark(line[end_idx_copy]))
		end_idx_copy++;
	*end_idx = end_idx_copy;
}
