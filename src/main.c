/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:52:10 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 00:49:15 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"
#include "signal_handler/signal_handler.h"
#include "command_list/cmd_list.h"
#include "libft.h"
#include "functions.h"
#include "environment_variables/env.h"
#include "search_executable/search_executable.h"

// readline
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <stdbool.h>
#include <stdlib.h>

// getcwd
#include <unistd.h>

// stat
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// signal
#include <signal.h>

#include "execution/execution.h"

bool	contains_only_spaces(char *line)
{
	while (ft_isspace(*line))
		line++;
	return (*line == '\0');
}

void	_eof_exit(int history_file)
{
	if (history_file != -1)
		close(history_file);
	printf("exit\n");
	env_free(&(minishell()->env));
	rl_clear_history();
	exit(minishell()->exit_status);
}

void	_read_and_execute_line(int history_file)
{
	char	*line;

	sigint_sigquit_handler(MINISHELL);
	line = readline("minishell $ ");
	if (line == NULL)
		_eof_exit(history_file);
	if (minishell()->received_signal == RECEIVED_SIGINT)
	{
		free(line);
		minishell()->received_signal = NONE;
		return ;
	}
	add_history(line);
	if (history_file != -1)
		ft_dprintf(history_file, "\n%s", line);
	if (contains_only_spaces(line))
	{
		free(line);
		return ;
	}
	execute_line(line);
	free(line);
}

int	main(void)
{
	int	history_file;

	if (!isatty(STDIN_FILENO))
		return (0);
	minishell_init();
	env_init(&(minishell()->env));
	history_file = read_history_from_file();
	while (true)
		_read_and_execute_line(history_file);
}
