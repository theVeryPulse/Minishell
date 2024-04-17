/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _apply_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:42:21 by Philip            #+#    #+#             */
/*   Updated: 2024/04/17 17:56:59 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../command_list/cmd_list.h"
#include "../minishell/minishell.h"
#include "../signal_handler/signal_handler.h" /* heredoc_sigint */
#include "../built_in/built_in.h"
#include "../free/free.h"
#include "libft.h" /* ft_strlen */
#include <fcntl.h> /* open */
#include <unistd.h> /* STDIN_FILENO */
#include <signal.h> /* signal */
#include <readline/readline.h> /* rl_event_hook, rl_outstream */

static int	_open_heredoc_temp_file_for_write(void)
{
	int	fd;

	if (access(HEREDOC_FILE, F_OK | R_OK | W_OK) != 0)
		unlink(HEREDOC_FILE);
	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0755);
	return (fd);
}

int	empty(void)
{
	return (0);
}

/**
 * @brief
 *
 * @param delimiter
 * @note The process itself first finishes heredoc before executing any built-in
 *       or external programs.
 * @todo Handle signals
 */
void	heredoc(char *delimiter, int stdin_copy)
{
	char	*line;
	int		heredoc_fd;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_sigint);
	rl_event_hook = &empty;
	dup2(stdin_copy, STDIN_FILENO);
	rl_outstream = stderr;
	heredoc_fd = _open_heredoc_temp_file_for_write();
	while (minishell()->received_signal == NONE)
	{
		line = readline("> ");
		if (!line)
		{
			ft_dprintf(STDERR_FILENO,
				"minishell: warning: here-document delimited by end-of-line "
				"(wanted `END')\n");
			break ;
		}
		if (minishell()->received_signal == RECEIVED_SIGINT)
			break ;
		if (ft_strncmp(delimiter, line, ft_strlen(delimiter) + 1) == 0)
			break ;
		if (line)
			write(heredoc_fd, line, ft_strlen(line));
		free_and_null((void **)&line);
	}
	close(heredoc_fd);
	free_and_null((void **)&line);
	rl_outstream = stdout;
}

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
void	_apply_redirects(t_cmd_list *cmd, int stdin_copy)
{
	char	**redirect;
	int		fd;

	if (!cmd->redirects)
		return ;
	redirect = cmd->redirects;
	while (*redirect)
	{
		if ((*redirect)[0] == '<')
		{
			if ((*redirect)[1] == '<')
			{
				heredoc(&(*redirect)[2], stdin_copy);
				if (minishell()->received_signal != NONE)
					return ;
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
		close(fd);
		redirect++;
	}
}
