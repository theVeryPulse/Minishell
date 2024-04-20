/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:52:10 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 17:24:04 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"
#include "execution/execution.h" /* execute_line */
#include "module_functions.h" /* read_history_from_file */
#include "environment_variables/env.h" /* env_free */
#include "signal_handler/signal_handler.h" /* sigint_sigquit_handler */
#include "libft.h" /* ft_dprintf */
#include <readline/readline.h>
#include <readline/history.h> /* add_history */
#include <stdbool.h>
#include <stdio.h> /* printf */
#include <stdlib.h> /* free */
#include <unistd.h> /* isatty,  */

static void	_read_and_execute_line(int history_file);
static void	_eof_exit(int history_file);
static bool	contains_only_spaces(char *line);

int	main(void)
{
	int	history_file;

	if (!isatty(STDIN_FILENO))
		return (0);
	minishell_init();
	history_file = read_history_from_file();
	while (true)
		_read_and_execute_line(history_file);
}

static void	_read_and_execute_line(int history_file)
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

static void	_eof_exit(int history_file)
{
	if (history_file != -1)
		close(history_file);
	printf("exit\n");
	env_free(&(minishell()->env));
	rl_clear_history();
	exit(minishell()->exit_status);
}

static bool	contains_only_spaces(char *line)
{
	while (ft_isspace(*line))
		line++;
	return (*line == '\0');
}
