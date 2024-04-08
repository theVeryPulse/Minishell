/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:04:02 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 15:04:09 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_list.h"
#include "libft.h"
#include "character_checks.h"
#include "syntax_analyzer.h"
#include <stddef.h>
#include <stdio.h>

static char	last_character_of_string(char *str);
static void	print_error_message(t_type unexpected, char *next_redirect);
static int	check_redirects(t_cmd_list *cmd);

/**
 * @brief  Checks if all commands have correct syntax. Returns 1 upon finding
 *         any error, else return 0.
 * 
 * @param  cmds A pointer to the first node of the command list.
 * @return int Returns 1 if any error is found, otherwise returns 0.
 * @note   Incorrect syntax include:
 *         1. Empty command: both redirect and arguments are empty;
 *         2. Missing filename/delimiter for redirection: `<<><`, `<<|`, etc;
 */
int	analyze_syntax(t_cmd_list *cmds)
{
	t_cmd_list	*cmd;

	if (!cmds)
		return (0);
	cmd = cmds;
	while (cmd)
	{
		if (cmd->cmd_argv == NULL && cmd->redirects == NULL)
		{
			print_error_message(PIPE, NULL);
			return (1);
		}
		if (check_redirects(cmd) != 0)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

/**
 * Internal helper function for `check_redirects()`
 */
static char	last_character_of_string(char *str)
{
	while (*(str + 1))
		str++;
	return (*str);
}

/**
 * Internal helper function for `check_redirects()`.
 * 
 * @brief Prints the error message to STDERR
 * 
 * @param unexpected The unexpected character after redirect symbol
 * @param next_redirect The following redirect, use NULL when unexpected
 *                      character is not `<` or `>`
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
		ft_strlcpy(unexpected_redirect_symbols, next_redirect, 3);
		if (next_redirect[0] == next_redirect[1])
			unexpected_redirect_symbols[2] = '\0';
		else
			unexpected_redirect_symbols[1] = '\0';
		ft_dprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token `%s'\n",
			unexpected_redirect_symbols);
	}
}

/* 
Internal helper function for `analyze_syntax()`

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
