/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siev <siev@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:52:10 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 23:45:55 by siev             ###   ########.fr       */
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

bool	contains_only_spaces(char *line)
{
	while (ft_isspace(*line))
		line++;
	return (*line == '\0');
}

int	main(void)
{
	if (!isatty(STDIN_FILENO))
		return (0);
	
	
	// char	buffer[100];
	// getcwd(buffer, 100);
	// printf("%s\n", buffer);
	// printf("%s\n", *__environ);
	// printf("ttyname: %s\n", ttyname(STDIN_FILENO));
	// printf("STDIN isatty = %d\n", isatty(STDIN_FILENO));
	// printf("STDOUT isatty = %d\n", isatty(STDOUT_FILENO));
	// printf("STDERR isatty = %d\n", isatty(STDERR_FILENO));

	// add_history("Second to latest command");
	// add_history("Latest command");

	char		*line;
	int			history_file;

	minishell_init();
	env_init(&(minishell()->env));
	history_file = read_history_from_file();
	while (true)
	{
		signal(SIGINT, minishell_sigint);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell $ ");
		if (line == NULL) /* crtl+d EOF */
		{
			if (history_file != -1)
				close(history_file);
			printf("exit\n");
			env_free(&(minishell()->env));
			rl_clear_history();
			return (minishell()->exit_status);
		}
		if (minishell()->received_signal == RECEIVED_SIGINT)
		{
			free(line);
			minishell()->received_signal = NONE;
			continue ;
		}
		add_history(line);
		if (history_file != -1)
			ft_dprintf(history_file, "\n%s", line);
		if (contains_only_spaces(line))
			continue ;
		minishell()->cmds = analyze_lexemes(line);
		// print_cmds(cmds); /* Develop */
		if (analyze_syntax(minishell()->cmds) == 0)
		{
			expand_arguments(minishell()->cmds, minishell()->env);
			search_exec_and_replace_arg_in_cmds(minishell()->cmds, minishell()->env);
			// print_cmds(cmds); /* Develop */
			check_redirect_files(minishell()->cmds);
			execute_cmds(minishell()->cmds, &(minishell()->env));
		}
		cmd_list_free(&(minishell()->cmds));
		free(line);
		// break;
	}
}
