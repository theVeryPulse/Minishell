/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   module_functions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:43:44 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 17:10:11 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODULE_FUNCTIONS_H
# define MODULE_FUNCTIONS_H

# include "command_list/t_cmd_list.h"
# include "environment_variables/t_env.h"

/* This header file contains external functions from the modules */

/* Working history */

extern int			read_history_from_file(void);

/* Lexical analysis */

extern t_cmd_list	*analyze_lexemes(const char *line);

/* Syntax analysis */

extern int			analyze_syntax(t_cmd_list *cmds);

/* Expand argument */

extern void			expand_arguments(t_cmd_list *cmds, t_env *env);

/* Check redirect files */

extern void			check_redirect_files(t_cmd_list *cmds);

/* Test functions */

extern void			print_cmds(t_cmd_list *cmds);

#endif
