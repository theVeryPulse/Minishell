/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:43:44 by Philip            #+#    #+#             */
/*   Updated: 2024/04/15 12:58:29 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "command_list/cmd_list.h"
# include "environment_variables/env.h"

/* Working history */

int			read_history_from_file(void);

/* Lexical analysis */

t_cmd_list	*analyze_lexemes(const char *line);

/* Syntax analysis */

int			analyze_syntax(t_cmd_list *cmds);

/* Search executable */

// void		search_executable(t_cmd_list *cmds, t_env *env);

/* Expand argument */

void		expand_arguments(t_cmd_list *cmds, t_env *env);

/*  */

void		check_redirect_files(t_cmd_list *cmds);

/* Execute commands */

void		execute_cmds(t_cmd_list *cmds, t_env **env);

/* Test functions */

void		print_cmds(t_cmd_list *cmds);

#endif
