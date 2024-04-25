/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _apply_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:42:21 by Philip            #+#    #+#             */
/*   Updated: 2024/04/25 23:37:10 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_execution.h" /* _heredoc */
#include "_heredoc.h" /* HEREDOC_FILE */
#include "../command_list/t_cmd_list.h" /* t_cmd_list */
#include "../minishell/minishell.h" /* minishell */
#include <fcntl.h> /* open */
#include <unistd.h> /* STDIN_FILENO */

extern void	_apply_redirects(t_cmd_list *cmd);
static int	_open_file_or_heredoc(char **redirect, char *heredoc);

/**
 * @brief Applies the redirection for current command.
 *        `<`: input file
 *        `<<`: heredoc
 *        `>`: output file overwrite
 *        `>>`: output file append
 *
 * @param cmd Command to apply redirects to.
 */
extern void	_apply_redirects(t_cmd_list *cmd)
{
	char	**redirect;
	int		fd;

	fd = -1;
	if (!cmd->redirects)
		return ;
	redirect = cmd->redirects;
	while (*redirect && minishell()->received_signal == NONE)
	{
		fd = _open_file_or_heredoc(redirect, cmd->heredoc);
		if (fd != -1)
			close(fd);
		redirect++;
	}
}

static int	_open_file_or_heredoc(char **redirect, char *heredoc)
{
	int	fd;

	fd = -1;
	if ((*redirect)[0] == '<')
	{
		if ((*redirect)[1] == '<')
		{
			_heredoc(&(*redirect)[2], heredoc);
			if (minishell()->received_signal != NONE)
				return (-1);
			fd = open(heredoc, O_RDONLY);
		}
		else
			fd = open(&(*redirect)[1], O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	else if ((*redirect)[0] == '>')
	{
		if ((*redirect)[1] == '>')
			fd = open(&(*redirect)[2], O_WRONLY | O_APPEND);
		else
			fd = open(&(*redirect)[1], O_WRONLY | O_TRUNC);
		dup2(fd, STDOUT_FILENO);
	}
	return (fd);
}
