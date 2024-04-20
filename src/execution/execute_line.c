/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:41:00 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 02:10:24 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell/minishell.h"
#include "../functions.h"
#include "../command_list/cmd_list.h"
#include "../search_executable/search_executable.h"

void	execute_line(char *line)
{
	minishell()->cmds = analyze_lexemes(line);
	if (analyze_syntax(minishell()->cmds) == 0)
	{
		expand_arguments(minishell()->cmds, minishell()->env);
		search_exec_and_replace_arg_in_cmds(minishell()->cmds,
			minishell()->env);
		check_redirect_files(minishell()->cmds);
		execute_commands(minishell()->cmds, &(minishell()->env));
	}
	cmd_list_free(&(minishell()->cmds));
}
