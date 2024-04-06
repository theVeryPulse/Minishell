/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:43:44 by Philip            #+#    #+#             */
/*   Updated: 2024/04/06 19:56:14 by Philip           ###   ########.fr       */
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
t_cmd_list	*analyze_lexemes(const char *line);
int			analyze_syntax(t_cmd_list *cmds);

/* Environment variables */

void		build_env_stack(t_env_stack	**stack);
void		add_to_env(t_env_stack **stack, char *name_value);
char		*find_env_value_by_name(t_env_stack *stack, const char *name);
void		remove_from_env_by_name(t_env_stack **stack, const char *name);
void		free_env_stack(t_env_stack **stack);

/* Test functions */

void		print_cmds(t_cmd_list *cmds);

#endif
