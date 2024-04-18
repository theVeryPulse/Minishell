/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:41:00 by Philip            #+#    #+#             */
/*   Updated: 2024/04/18 23:48:33 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell/minishell.h"
#include "../functions.h"
#include "../command_list/cmd_list.h"
#include "../search_executable/search_executable.h"

void	execute_line(char *line)
{
	minishell()->cmds = analyze_lexemes(line);
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
}
