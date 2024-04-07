/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:43:44 by Philip            #+#    #+#             */
/*   Updated: 2024/04/07 02:48:53 by Philip           ###   ########.fr       */
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

void		build_env_stack(t_env_stack	**stack);
void		update_in_env(t_env_stack **stack, const char *name_value);
char		*find_env_value_by_name(t_env_stack *stack, const char *name);
void		remove_from_env_by_name(t_env_stack **stack, const char *name);
char		**build_envp(t_env_stack *stack);
void		free_env_stack(t_env_stack **stack);

/* Search executable */

void		search_executable(t_cmd_list *cmds, t_env_stack *env);

/* Test functions */

void		print_cmds(t_cmd_list *cmds);

#endif
