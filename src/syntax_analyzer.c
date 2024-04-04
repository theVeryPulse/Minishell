/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:04:02 by Philip            #+#    #+#             */
/*   Updated: 2024/04/04 20:00:45 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stddef.h>
#include <stdio.h>

#define EMPTY_LIST (0)
#define SYNTAX_ERROR (1)

// In case that a redirect is ">>" without infile/outfile/delimiter:
// The missing delimiter's position would only be taken by `|` or `>` `<`
// If there is following redirection, they shall be the unexpected token
// If there is not, then `|` shall be the unexpected token
// A command with at least one argument or one redirection is valid.

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
	if (cmd->cmd_argv == NULL && cmd->redirects == NULL && cmds->next)
	{
		ft_dprintf(STDERR_FILENO, "minishell: syntax error near unexpected token `|'\n");
		return (SYNTAX_ERROR);
	}
	while (cmd)
	{
		if (!cmd->cmd_argv && !cmd->redirects)
		{
			
		}
		argument = cmd->cmd_argv;
		
		redirect = cmd->redirects;
	}
	
	return (0);
}


