/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:43:44 by Philip            #+#    #+#             */
/*   Updated: 2024/04/07 19:46:07 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "cmd_list.h"
# include "environment_variables.h"

/* Linked list of commands */

t_cmd_list	*cmd_list_new(void);
t_cmd_list	*cmd_list_last(t_cmd_list *list);
void		cmd_list_append(t_cmd_list **list, t_cmd_list *node);
void		cmd_list_free(t_cmd_list **list);

/* Working history */

int			read_history_from_file(void);

/* Lexical analysis */

t_cmd_list	*analyze_lexemes(const char *line);

/* Syntax analysis */

int			analyze_syntax(t_cmd_list *cmds);

/* Environment variables */

// void		env_build(t_env	**stack);
// void		env_update_name_value(t_env **stack, const char *name_value);
// char		*env_get_value_by_name(t_env *stack, const char *name);
// void		env_remove_by_name(t_env **stack, const char *name);
// char		**env_build_envp(t_env *stack);
// void		env_free(t_env **stack);

/* Search executable */

void		search_executable(t_cmd_list *cmds, t_env *env);

/* Test functions */

void		print_cmds(t_cmd_list *cmds);

#endif
