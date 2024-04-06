/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:04:02 by Philip            #+#    #+#             */
/*   Updated: 2024/04/06 01:27:17 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_list.h"
#include "libft.h"
#include "character_checks.h"
#include <stddef.h>
#include <stdio.h>

/**
 * Helper function for `check_redirects()`
 */
static char	last_character_of_string(char *str)
{
	while (*(str + 1))
		str++;
	return (*str);
}

/**
 * Helper type for `analyze_syntax()`.
 * 
 * @brief Define unexpected characters after redirect symbols
 * 
 */
typedef enum e_type
{
	/* Missing filename/delimiter: `>>|` `>|` `<|` `<<|` */
	PIPE,
	/* Missing filename/delimiter: `>>` `>` `<` `<<` */
	NEWLINE,
	/* Missing filename/delimiter: `>>>` `>>>>` `<<>` `<<<<` etc. */
	REDIRECT,
}	t_type;

/**
 * Helper function for `check_redirects()`
 * 
 * @brief 
 * 
 * @param unexpected 
 * @param next_redirect 
 */
static void	print_error_message(t_type unexpected, char *next_redirect)
{
	char	unexpected_redirect_symbols[3];

	if (unexpected == PIPE)
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token `|'\n");
	}
	else if (unexpected == NEWLINE)
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token `newline'\n");
	}
	else if (unexpected == REDIRECT)
	{
		if (next_redirect[0] == next_redirect[1])
			ft_strlcpy(unexpected_redirect_symbols, next_redirect, 3);
		else
			ft_strlcpy(unexpected_redirect_symbols, next_redirect, 3);
		ft_dprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token `%s'\n",
			unexpected_redirect_symbols);
	}
}

/* 
Helper function for `analyze_syntax()`

Three possible incorrect inputs:
| Input                       | Expected output                                |
| ----------------------------| ---------------------------------------------- |
| >>\| (followed by pipe)     | "syntax error near unexpected token `|'"       |
| >>> (followed by redirects) | "syntax error near unexpected token `>>'"      |
| >>  (followed by nothing)   | "syntax error near unexpected token `newline'" |
*/
static int	check_redirects(t_cmd_list *cmd)
{
	char	*redirect;
	char	**redirects;

	if (!cmd->redirects)
		return (0);
	redirects = cmd->redirects;
	redirect = *redirects;
	while (redirect)
	{
		if (is_redirect(last_character_of_string(redirect)))
		{
			if ((redirects + 1) && *(redirects + 1))
				print_error_message(REDIRECT, *(redirects + 1));
			else if (!cmd->next)
				print_error_message(NEWLINE, NULL);
			else if (cmd->next)
				print_error_message(PIPE, NULL);
			return (1);
		}
		redirect = *(++redirects);
	}
	return (0);
}


int	analyze_syntax(t_cmd_list *cmds)
{
	t_cmd_list	*cmd;

	if (!cmds)
		return (0);
	cmd = cmds;
	while (cmd)
	{
		if (cmd->cmd_argv == NULL && cmd->redirects == NULL && cmd->next)
		/* There is a following command but current command is empty,
		   meaning there is an unexpected `|` */
		{
			ft_dprintf(STDERR_FILENO, "minishell: syntax error near unexpected token `|'\n");
			return (1);
		}
		if (check_redirects(cmd) != 0)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}


