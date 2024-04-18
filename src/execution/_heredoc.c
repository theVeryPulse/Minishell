/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _heredoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:31:53 by Philip            #+#    #+#             */
/*   Updated: 2024/04/18 18:47:11 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_heredoc.h"
#include "../minishell/minishell.h" /* minishell */
#include "../signal_handler/signal_handler.h" /* heredoc_sigint */
#include "../free/free.h"
#include "libft.h" /* ft_strlen, ft_dprintf */
#include <readline/readline.h> /* rl_event_hook, rl_outstream */
#include <signal.h> /* signal  */
#include <fcntl.h> /* open */
#include <unistd.h>

#include "t_fd_action.h"
/* Temporary */int	_stdin_stdout(t_fd_action action);

extern void	_heredoc(char *delimiter);
static void	heredoc_setup(void);
static int	_open_heredoc_temp_file_for_write(void);
static int	end_readline(void);

/**
 * @brief Reads input from stdin and writes to a temporary file defined by 
 *        macro HEREDOC_FILE.
 *
 * @param delimiter A string noting the end of heredoc.
 * @param stdin_copy A copy of stdin used to reset fildes to read from terminal.
 * @note The process itself first finishes heredoc before executing any built-in
 *       or external programs.
 */
extern void	_heredoc(char *delimiter)
{
	char	*line;
	int		heredoc_fd;

	heredoc_setup();
	heredoc_fd = _open_heredoc_temp_file_for_write();
	while (minishell()->received_signal == NONE)
	{
		line = readline("> ");
		if (!line)
		{
			ft_dprintf(STDERR_FILENO, "minishell: warning: here-document"
				" delimited by end-of-line (wanted `END')\n");
			break ;
		}
		if (minishell()->received_signal == RECEIVED_SIGINT
			|| ft_strncmp(delimiter, line, ft_strlen(delimiter) + 1) == 0)
			break ;
		ft_dprintf(heredoc_fd, "%s\n", line);
		free_and_null((void **)&line);
	}
	close(heredoc_fd);
	free_and_null((void **)&line);
	rl_outstream = stdout;
}

static void	heredoc_setup()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_sigint);
	rl_event_hook = &end_readline;
	rl_outstream = stderr;
	dup2(_stdin_stdout(LOOKUP_STDIN), STDIN_FILENO);
}

static int	_open_heredoc_temp_file_for_write(void)
{
	int	fd;

	if (access(HEREDOC_FILE, F_OK | R_OK | W_OK) != 0)
		unlink(HEREDOC_FILE);
	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0755);
	return (fd);
}

static int	end_readline(void)
{
	return (0);
}
