/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_script_child.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:32:07 by Philip            #+#    #+#             */
/*   Updated: 2024/04/19 00:07:32 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../functions.h"
#include "../minishell/minishell.h"
#include "../environment_variables/env.h"
#include "../search_executable/search_executable.h"
#include "../command_list/cmd_list.h"
#include "libft.h"
#include <stdbool.h>
#include <stdlib.h> /* free */
#include <unistd.h> /* STDERR_FILENO */
#include <signal.h> /* signal */
#include <fcntl.h> /* open */
#include <readline/readline.h> /* rl_clear_history */
#include <errno.h>

// [ ] combine this file with _execute_shell_script.c


void	execute_line(char *line); /* [ ] Temporary */

static bool	contains_only_spaces(char *line)
{
	while (ft_isspace(*line))
		line++;
	return (*line == '\0');
}

void	_read_line_from_file_and_execute(int file)
{
	char	*line_without_nl;
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	line = get_next_line(file);
	if (line == NULL) /* EOF */
	{
		env_free(&(minishell()->env));
		exit (minishell()->exit_status);
	}
	if (contains_only_spaces(line))
	{
		free(line);
		return ;
	}
	line_without_nl = ft_strtrim(line, "\n");
	ft_dprintf(STDERR_FILENO, "$ %s\n", line_without_nl);
	execute_line(line_without_nl);
	free(line_without_nl);
	free(line);
}

void	execute_script_child(const char *filepath)
{
	int	file;

	ft_dprintf(STDERR_FILENO, "executing %s\n", filepath);
	rl_clear_history();
	file = open(filepath, O_RDONLY);
	if (file == -1)
	{
		perror(filepath);
		exit(1);
	}
	minishell_free();
	minishell_init();
	while (true)
		_read_line_from_file_and_execute(file);
}
