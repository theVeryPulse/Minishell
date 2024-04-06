/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:52:10 by Philip            #+#    #+#             */
/*   Updated: 2024/04/06 16:21:39 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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

void	prompt_on_new_line()
{
	printf("\n%s", rl_prompt);
}

int	main(void)
{
	if (!isatty(STDIN_FILENO))
		return (0);
	
	signal(SIGINT, prompt_on_new_line);
	signal(SIGQUIT, SIG_IGN);
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
	t_cmd_list	*cmds;
	int			history_file;

	history_file = read_history_from_file();
	while (true)
	{
		line = readline("minishell $ ");
		// printf("((%s))\n", rl_line_buffer);
		if (line == NULL) /* crtl+d EOF */
		{
			if (history_file != -1)
				close(history_file);
			return (0);
		}
		if (ft_strncmp("exit", line, 5) == 0) // Incomplete, exit should return
		{
			free(line);
			rl_clear_history();
			return (0);
		}
		add_history(line);
		if (history_file != -1)
			ft_dprintf(history_file, "\n%s", line);
		if (contains_only_spaces(line))
			continue ;
		cmds = analyze_lexemes(line);
		print_cmds(cmds); /* Develop */
		analyze_syntax(cmds);
		cmd_list_free(&cmds);
		free(line);
		// break;
	}
	return 0;
}
