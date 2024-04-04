/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:49:09 by Philip            #+#    #+#             */
/*   Updated: 2024/04/04 18:58:57 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "character_checks.h"
#include <stdio.h>

// Check this command
// <output1 <output2 <outputnotexist <output4 cat >b > c  > d


char	**list_to_string_array(t_list *list)
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

void	free_all_nodes_leave_content(t_list **head)
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

// Stops at a metacharacter
// 123"123"123'123'<
// 123"123 123"123|
// "123 123"123'123'>
// "123"123'123
// Should be used for arguments and redirect filenames/delimters
// 'E'""END
// > >> < << should be handled outside this function
char	*get_next_word(const char *line, size_t *i)
{
	size_t	i_copy;
	char	*word;
	char	*close_quote;
	size_t	end_idx; // Copy until before this index

	i_copy = *i;
	if (is_metacharacter(line[i_copy]))
		return (ft_calloc(1, sizeof(char)));
	while (ft_isspace(line[i_copy]))
		i_copy++;
	/* Duplicate the complete word */
	end_idx = i_copy;
	/* |-- Finds out where the word ends */
	while (line[end_idx]
		&& !is_metacharacter(line[end_idx]))
	{
		if (is_quotation_mark(line[end_idx]))
		{
			close_quote = ft_strchr(&line[end_idx + 1], line[end_idx]);
			if (close_quote)
			{
				end_idx = close_quote - line + 1;
			}
			else
			{
				while (line[end_idx])
					end_idx++;
			}
		}
		else
		{
			while (line[end_idx]
				&& !is_metacharacter(line[end_idx])
				&& !is_quotation_mark(line[end_idx]))
			{
				end_idx++;
			}
		}
	}
	word = ft_strndup(&line[i_copy], end_idx - i_copy);
	*i = end_idx;
	return (word);
}

void	add_this_cmd_to_list(t_cmd_list	**cmds, t_cmd_list *this_cmd,
		t_list **this_cmd_argv_list, t_list **this_cmd_redirect_list)
{
	this_cmd->cmd_argv = list_to_string_array(*this_cmd_argv_list);
	this_cmd->redirects = list_to_string_array(*this_cmd_redirect_list);
	free_all_nodes_leave_content(this_cmd_argv_list);
	free_all_nodes_leave_content(this_cmd_redirect_list);
	cmd_list_append(cmds, this_cmd);
}

// Lexical analysis, sometimes referred to as tokenizer
// Translates line into tokens. 
// $env_var ' " < > << >> |
// echo -n 123 321
// echo -n 123 321 | cat
t_cmd_list	*analyze_leximes(const char *line)
{
	size_t		i;
	t_cmd_list	*cmds;
	t_cmd_list	*this_cmd;
	t_list		*this_cmd_argv_list;
	t_list		*this_cmd_redirect_list;

	this_cmd_argv_list = NULL;
	this_cmd_redirect_list = NULL;
	cmds = NULL;
	this_cmd = cmd_list_new();
	i = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (line[i] == '|')
		{
			add_this_cmd_to_list(&cmds, this_cmd, &this_cmd_argv_list,
				&this_cmd_redirect_list);
			this_cmd = cmd_list_new();
			i++;
		}
		else if (is_redirect(line[i]))
		{
			char	*redirect_symbols;
			char	*word;

			if (line[i + 1] == line[i])
				redirect_symbols = ft_strndup(&line[i++], 2);
			else
				redirect_symbols = ft_strndup(&line[i], 1);
			i++;
			while (ft_isspace(line[i]))
				i++;
			word = get_next_word(line, &i);
			ft_lstadd_back(&this_cmd_redirect_list,
				ft_lstnew((void *)ft_strjoin(redirect_symbols,
					word)));
			free(redirect_symbols);
			free(word);
			printf("\"%s\" added to list\n", (char *)ft_lstlast(this_cmd_redirect_list)->content);
		}
		else
		{
			char	*word;

			word = get_next_word(line, &i);
			ft_lstadd_back(&this_cmd_argv_list,
					ft_lstnew((void *)word));
			printf("\"%s\" added to list\n", (char *)ft_lstlast(this_cmd_argv_list)->content);
		}
	}
	add_this_cmd_to_list(&cmds, this_cmd, &this_cmd_argv_list,
				&this_cmd_redirect_list);

	/* List nodes should be freed, but the content should not be freed */
	
	// return (cmds);
	print_and_free_cmds(cmds);
}

