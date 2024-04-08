/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer_part2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:34:50 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 16:54:37 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_next_word_and_update_i(const char *line, size_t *i);
static void	set_end_idx_to_close_quote(const char *line, size_t *end_idx);
static void	set_end_idx_to_word_end(const char *line, size_t *end_idx);

void	add_redirect_and_update_i(t_list **redirects, const char *line,
			size_t *i)
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
	word = get_next_word_and_update_i(line, &i_copy);
	redirect_str = ft_strjoin(redirect_symbols, word);
	ft_lstadd_back(redirects, ft_lstnew((void *)redirect_str));
	free(redirect_symbols);
	free(word);
	*i = i_copy;
	printf("\"%s\" added to list\n", (char *)ft_lstlast(*redirects)->content); /* Test */
}

void	add_argument_and_update_i(t_list **arguments, const char *line,
			size_t *i)
{
	char	*word;
	size_t	i_copy;

	i_copy = *i;
	word = get_next_word_and_update_i(line, &i_copy);
	ft_lstadd_back(arguments, ft_lstnew((void *)word));
	*i = i_copy;
	// printf("\"%s\" added to list\n", (char *)ft_lstlast(arguments)->content);
}

// Stops at a metacharacter
// 123"123"123'123'<
// 123"123 123"123|
// "123 123"123'123'>
// "123"123'123
// Should be used for arguments and redirect filenames/delimiters
// 'E'""END
// > >> < << should be handled outside this function
static char	*get_next_word_and_update_i(const char *line, size_t *i)
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
			set_end_idx_to_close_quote(line, &end_idx);
		else
			set_end_idx_to_word_end(line, &end_idx);
	}
	word = ft_strndup(&line[i_copy], end_idx - i_copy);
	*i = end_idx;
	return (word);
}

static void	set_end_idx_to_close_quote(const char *line, size_t *end_idx)
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

static void	set_end_idx_to_word_end(const char *line, size_t *end_idx)
{
	size_t	end_idx_copy;

	end_idx_copy = *end_idx;
	while (line[end_idx_copy]
		&& !is_metacharacter(line[end_idx_copy])
		&& !is_quotation_mark(line[end_idx_copy]))
		end_idx_copy++;
	*end_idx = end_idx_copy;
}
