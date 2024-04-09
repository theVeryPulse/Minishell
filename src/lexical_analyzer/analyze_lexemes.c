/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_lexemes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:46:38 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 20:42:55 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_lexical_analyzer.h"
#include "../character_checks.h"
#include "../command_list/cmd_list.h"
#include "libft.h"
#include <stdio.h>
#include <stdarg.h>

static void	_set_to_null(int n, ...);
static void	_skip_spaces(const char *line, size_t *i);
static void	_add_argument_and_update_i(t_list **arguments, const char *line,
				size_t *i);
static void	_add_redirect_and_update_i(t_list **redirects, const char *line,
				size_t *i);

/*
analyze_lexemes
    |
    |-- _set_to_null()
    |
    |-- _skip_spaces()
    |
    |-- _add_redirect_and_update_i() [ ]
    |       |
    |-- _add_argument_and_update_i() [ ]
    |       |
    |       |-- _get_next_word_and_update_i() [ ]
    |               |
    |               |-- _set_end_idx_to_close_quote()
    |               |-- _set_end_idx_to_word_end()
    |
    |-- _add_this_cmd_to_list() [ ]
            |
            |-- _list_to_string_array()
            |-- _free_all_nodes_leave_content()
 */

/**
 * @brief Lexical analysis, also known as tokenizer or lexer. Translates line
 *        into tokens.
 * 
 * @param line the input string to be analyzed.
 * @return `t_cmd_list*` A linked list of commands, each node is a command with
 *         arguments and redirects as string arrays.
 */
t_cmd_list	*analyze_lexemes(const char *line)
{
	size_t		i;
	t_cmd_list	*cmds;
	t_cmd_list	*this_cmd;
	t_list		*arguments;
	t_list		*redirects;

	_set_to_null(3, &arguments, &redirects, &cmds);
	this_cmd = cmd_list_new();
	i = 0;
	while (line[i])
	{
		_skip_spaces(line, &i);
		if (line[i] == '|')
		{
			_add_this_cmd_to_list(&cmds, this_cmd, &arguments, &redirects);
			this_cmd = cmd_list_new();
			i++;
		}
		else if (is_redirect(line[i]))
			_add_redirect_and_update_i(&redirects, line, &i);
		else
			_add_argument_and_update_i(&arguments, line, &i);
	}
	_add_this_cmd_to_list(&cmds, this_cmd, &arguments, &redirects);
	return (cmds);
}

static void	_set_to_null(int n, ...)
{
	va_list	ap;
	void	**ptr;

	va_start(ap, n);
	while (n)
	{
		ptr = va_arg(ap, void **);
		*ptr = NULL;
		n--;
	}
	va_end(ap);
}

static void	_skip_spaces(const char *line, size_t *i)
{
	size_t	i_copy;

	i_copy = *i;
	while (line[i_copy] && ft_isspace(line[i_copy]))
		i_copy++;
	*i = i_copy;
}

static void	_add_redirect_and_update_i(
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

static void	_add_argument_and_update_i(
			t_list **arguments, const char *line, size_t *i)
{
	char	*word;
	size_t	i_copy;

	i_copy = *i;
	word = _get_next_word_and_update_i(line, &i_copy);
	ft_lstadd_back(arguments, ft_lstnew((void *)word));
	*i = i_copy;
	// printf("\"%s\" added to list\n", (char *)ft_lstlast(arguments)->content);
}
