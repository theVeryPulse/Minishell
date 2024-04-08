/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer_part1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:49:09 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 17:04:51 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexical_analyzer.h"
#include "cmd_list.h"
#include "character_checks.h"
#include "libft.h"
#include <stdarg.h>
#include <stdio.h>

static void	set_to_null(int n, ...);
static void	skip_spaces(const char *line, size_t *i);

// Check this command
// <output1 <output2 <outputnotexist <output4 cat >b > c  > d

/*
analyze_lexemes
    |
    |-- set_to_null()
    |
    |-- skip_spaces()
    |
    |part2
    |-- add_redirect_and_update_i()
    |       |
    |-- add_argument_and_update_i()
    |       |
    |       |-- get_next_word_and_update_i()
    |               |
    |               |-- set_end_idx_to_close_quote()
    |               |-- set_end_idx_to_word_end()
    |
    |part3
    |-- add_this_cmd_to_list()
            |
            |-- list_to_string_array()
            |-- free_all_nodes_leave_content()
 */

// Lexical analysis, sometimes referred to as tokenizer
// Translates line into tokens. 
// $env_var ' " < > << >> |
// echo -n 123 321
// echo -n 123 321 | cat
t_cmd_list	*analyze_lexemes(const char *line)
{
	size_t		i;
	t_cmd_list	*cmds;
	t_cmd_list	*this_cmd;
	t_list		*arguments;
	t_list		*redirects;

	set_to_null(3, &arguments, &redirects, &cmds);
	this_cmd = cmd_list_new();
	i = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (line[i] == '|')
		{
			add_this_cmd_to_list(&cmds, this_cmd, &arguments, &redirects);
			this_cmd = cmd_list_new();
			i++;
		}
		else if (is_redirect(line[i]))
			add_redirect_and_update_i(&redirects, line, &i);
		else
			add_argument_and_update_i(&arguments, line, &i);
	}
	add_this_cmd_to_list(&cmds, this_cmd, &arguments, &redirects);
	return (cmds);
}

static void	set_to_null(int n, ...)
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

static void	skip_spaces(const char *line, size_t *i)
{
	size_t	i_copy;

	i_copy = *i;
	while (line[i_copy] && ft_isspace(line[i_copy]))
		i_copy++;
	*i = i_copy;
}
