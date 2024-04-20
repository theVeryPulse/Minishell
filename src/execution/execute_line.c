/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:41:00 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 16:50:00 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell/minishell.h"
#include "../module_functions.h"
#include "../command_list/cmd_list.h" /* cmd_list_free */
#include "../search_executable/search_executable.h"

/**
 * @brief Executes a line of input: analyze lexemes, check syntax, expand
 *        arguments, search executables, check redirect files, and execute
 *        commands.
 * 
 * @param line The line to execute
 */
extern void	execute_line(char *line)
{
	minishell()->cmds = analyze_lexemes(line);
	if (analyze_syntax(minishell()->cmds) == 0)
	{
		expand_arguments(minishell()->cmds, minishell()->env);
		search_executable_in_commands(minishell()->cmds, minishell()->env);
		check_redirect_files(minishell()->cmds);
		execute_commands(minishell()->cmds, &(minishell()->env));
	}
	cmd_list_free(&(minishell()->cmds));
}
