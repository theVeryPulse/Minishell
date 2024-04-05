/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:04:02 by Philip            #+#    #+#             */
/*   Updated: 2024/04/05 22:58:30 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "cmd_list.h"
#include "libft.h"
#include "character_checks.h"
#include <stddef.h>
#include <stdio.h>

#define EMPTY_LIST (0)
#define SYNTAX_ERROR (1)

// In case that a redirect is ">>" without infile/outfile/delimiter:
// The missing delimiter's position would only be taken by `|` or `>` `<`
// If there is following redirection, they shall be the unexpected token
// If there is not, then `|` shall be the unexpected token
// A command with at least one argument or one redirection is valid.

static int	check_arguments(char **argument)
{
	if (!argument || !(*argument))
		return (0);
	
}

static int	check_redirects(char **redirects)
{
	size_t	i;
	char	*unexpected_str;
	char	*redirect;
	char	*next_redirect;

	unexpected_str = NULL;
	redirect = *redirects;
	// next_redirect = *(redirects + 1);
	while (redirect)
	{
		i = 0;
		while (redirect[i])
			i++;
		i--;
		if (is_redirect(redirect[i]))
		{
			if (redirects + 1 && *(redirects + 1))
			{
				next_redirect = *(redirects + 1);
				/* syntax error near unexpected token `>' */
				if (next_redirect[0] == next_redirect[1])
					unexpected_str = ft_strndup(next_redirect, 2);
				else
					unexpected_str = ft_strndup(next_redirect, 2);
				ft_dprintf(STDERR_FILENO,
					"minishell: syntax error near unexpected token `%s'\n", unexpected_str);
				free(unexpected_str);
			}
			else if (0) /* [ ] bash: syntax error near unexpected token `newline'  use command to check this */
			{

			}
			else
				ft_dprintf(STDERR_FILENO, "minishell: missing command after `|'\n");
			return (1);
		}
		redirect++;
		redirect = *redirects;
		// next_redirect = *(redirects + 1);
	}
	return (0);
}


int	analyze_syntax(t_cmd_list *cmds)
{
	t_cmd_list	*cmd;
	char		**argument;
	char		**redirect;

	if (!cmds)
		return (EMPTY_LIST);
	cmd = cmds;
	// There is a second command but first command is empty, meaning there is an
	// unexpected `|`
	while (cmd)
	{
		if (cmd->cmd_argv == NULL && cmd->redirects == NULL && cmd->next)
		{
			ft_dprintf(STDERR_FILENO, "minishell: syntax error near unexpected token `|'\n");
			return (SYNTAX_ERROR);
		}
		argument = cmd->cmd_argv;
		// [ ] Check arguments
		redirect = cmd->redirects;
		if (check_redirects(cmd->redirects) != 0)
		{
			return (1); /* Redirects error */
		}
		cmd = cmd->next;
	}
	
	return (0);
}


