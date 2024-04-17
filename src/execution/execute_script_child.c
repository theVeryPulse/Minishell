/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_script_child.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:32:07 by Philip            #+#    #+#             */
/*   Updated: 2024/04/17 19:14:57 by Philip           ###   ########.fr       */
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

static bool	contains_only_spaces(char *line)
{
	while (ft_isspace(*line))
		line++;
	return (*line == '\0');
}

void	execute_script_child(const char *filepath)
{
	char	*line;
	char	*line_without_nl;
	int		file;

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
	{
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
			continue ;
		}
		line_without_nl = ft_strtrim(line, "\n");
		ft_dprintf(STDERR_FILENO, "$ %s\n", line_without_nl);
		minishell()->cmds = analyze_lexemes(line_without_nl);
		// print_cmds(cmds); /* Develop */
		if (analyze_syntax(minishell()->cmds) == 0)
		{
			// print_cmds(minishell()->cmds); /* Develop */
			expand_arguments(minishell()->cmds, minishell()->env);
			search_exec_and_replace_arg_in_cmds(minishell()->cmds, minishell()->env);
			check_redirect_files(minishell()->cmds);
			execute_cmds(minishell()->cmds, &(minishell()->env));
		}
		cmd_list_free(&(minishell()->cmds));
		free(line_without_nl);
		free(line);
	}
}
