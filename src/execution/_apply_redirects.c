/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _apply_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:42:21 by Philip            #+#    #+#             */
/*   Updated: 2024/04/18 18:44:20 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h" /* _heredoc */
#include "_heredoc.h"
#include "../command_list/t_cmd_list.h" /* t_cmd_list */
#include "../minishell/minishell.h" /* minishell */
#include <fcntl.h> /* open */
#include <unistd.h> /* STDIN_FILENO */

extern void	_apply_redirects(t_cmd_list *cmd);
static int	_open_file_or_heredoc(char **redirect);

/**
 * @brief
 *
 * @param
 * @note Four occasions:
 *       `<`  : dup2(input_file_fd, STDIN_FILENO)
 *       `<<` : dup2(heredoc_temp_file, STDIN_FILENO)
 *       `>`  : dup2(output_file_fd, STDOUT_FILENO) O_WRONLY | O_APPEND
 *       `>>` : dup2(output_file_fd, STDOUT_FILENO) O_WRONLY | O_TRUNC
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
		_open_file_or_heredoc(redirect);
		if (fd != -1)
			close(fd);
		redirect++;
	}
}

static int	_open_file_or_heredoc(char **redirect)
{
	int	fd;

	fd = -1;
	if ((*redirect)[0] == '<')
	{
		if ((*redirect)[1] == '<')
		{
			_heredoc(&(*redirect)[2]);
			if (minishell()->received_signal != NONE)
				return (-1);
			fd = open(HEREDOC_FILE, O_RDONLY);
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
