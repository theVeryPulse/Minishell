/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:49:09 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 02:38:32 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "character_checks.h"
#include <stdio.h>

// Check this command
// <output1 <output2 <outputnotexist <output4 cat >b > c  > d

static char	**list_to_string_array(t_list *list);
static void	free_all_nodes_leave_content(t_list **head);
static void	add_this_cmd_to_list(t_cmd_list	**cmds, t_cmd_list *this_cmd,
				t_list **arguments, t_list **redirects);
static char	*get_next_word_and_update_i(const char *line, size_t *i);
static void	add_redirect_and_update_i(t_list **redirects, const char *line, size_t *i);
static void	add_argument_and_update_i(t_list **arguments, const char *line, size_t *i);

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
	char	*close_quote;
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
		{
			/* set_i_to_close_quote() */
			close_quote = ft_strchr(&line[end_idx + 1], line[end_idx]);
			if (close_quote)
				end_idx = close_quote - line + 1;
			else
			{
				while (line[end_idx])
					end_idx++;
			}
		}
		else
		{
			/* set_i_to_word_end() */
			while (line[end_idx]
					&& !is_metacharacter(line[end_idx])
					&& !is_quotation_mark(line[end_idx]))
				end_idx++;
		}
	}
	word = ft_strndup(&line[i_copy], end_idx - i_copy);
	*i = end_idx;
	return (word);
}

static void	add_this_cmd_to_list(t_cmd_list	**cmds, t_cmd_list *this_cmd,
		t_list **arguments, t_list **redirects)
{
	this_cmd->cmd_argv = list_to_string_array(*arguments);
	this_cmd->redirects = list_to_string_array(*redirects);
	free_all_nodes_leave_content(arguments);
	free_all_nodes_leave_content(redirects);
	cmd_list_append(cmds, this_cmd);
}

static void	add_redirect_and_update_i(t_list **redirects, const char *line, size_t *i)
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

static void	add_argument_and_update_i(t_list **arguments, const char *line, size_t *i)
{
	char	*word;
	size_t	i_copy;

	i_copy = *i;
	word = get_next_word_and_update_i(line, &i_copy);
	ft_lstadd_back(arguments, ft_lstnew((void *)word));
	*i = i_copy;
	// printf("\"%s\" added to list\n", (char *)ft_lstlast(arguments)->content);
}

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

	arguments = NULL;
	redirects = NULL;
	cmds = NULL;
	this_cmd = cmd_list_new();
	i = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
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

static char	**list_to_string_array(t_list *list)
{
	int		list_len;
	int		i;
	char	**string_array;

	if (!list)
	{
		return (NULL);
	}
	list_len = ft_lstsize(list);
	string_array = (char **)ft_calloc(list_len + 1, sizeof(char *));
	i = 0;
	while (i < list_len)
	{
		string_array[i] = (char *)list->content;
		list = list->next;
		i++;
	}
	return (string_array);
}

static void	free_all_nodes_leave_content(t_list **head)
{
	t_list	*node;
	t_list	*next_node;

	if (!head || !(*head))
		return ;
	node = *head;
	while (node)
	{
		next_node = node->next;
		free(node);
		node = next_node;
	}
	*head = NULL;
}
