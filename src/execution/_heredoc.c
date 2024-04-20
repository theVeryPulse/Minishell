/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _heredoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:31:53 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 17:00:26 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_execution.h" /* _stdin_stdou */
#include "_heredoc.h" /* HEREDOC_FILE */
#include "../minishell/minishell.h" /* minishell */
#include "../signal_handler/signal_handler.h" /* sigint_sigquit_handler */
#include "../free/free.h" /* free_and_null */
#include "libft.h" /* ft_strlen, ft_dprintf */
#include <readline/readline.h> /* rl_event_hook, rl_outstream */
#include <fcntl.h> /* open */
#include <unistd.h> /* STDIN_FILENO */

extern void	_heredoc(char *delimiter);
static void	_heredoc_setup(void);
static int	_open_heredoc_temp_file_for_write(void);
static int	_end_readline(void);

/**
 * @brief Reads input from stdin and writes to a temporary file defined by 
 *        macro HEREDOC_FILE.
 *
 * @param delimiter String noting the end of heredoc.
 * @note The minishell main process first finishes heredoc before executing a
 *       built-in or external programs.
 */
extern void	_heredoc(char *delimiter)
{
	char	*line;
	int		heredoc_fd;

	_heredoc_setup();
	heredoc_fd = _open_heredoc_temp_file_for_write();
	while (minishell()->received_signal == NONE)
	{
		line = readline("> ");
		if (!line)
		{
			ft_dprintf(STDERR_FILENO, "minishell: warning: here-document"
				" delimited by end-of-line (wanted `%s')\n", delimiter);
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

static void	_heredoc_setup(void)
{
	sigint_sigquit_handler(HEREDOC);
	rl_event_hook = &_end_readline;
	rl_outstream = stderr;
	dup2(_stdin_stdout(LOOKUP_STDIN_COPY), STDIN_FILENO);
}

static int	_open_heredoc_temp_file_for_write(void)
{
	int	fd;

	if (access(HEREDOC_FILE, F_OK | R_OK | W_OK) != 0)
		unlink(HEREDOC_FILE);
	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0755);
	return (fd);
}

static int	_end_readline(void)
{
	return (0);
}
