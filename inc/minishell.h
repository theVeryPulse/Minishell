/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:43:44 by Philip            #+#    #+#             */
/*   Updated: 2024/04/04 20:07:07 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
typedef struct s_cmd_list t_cmd_list;

struct s_cmd_list
{
	// Null terminated array of arguments
	// Example: `{"echo", "-n", "123", "$VAR$VAR", NULL}`
	char		**cmd_argv; 
	// Null terminated array of redirects
	// Example: `{"<infile", "<<delimiter", ">outfile", ">>outfile"}`
	char		**redirects; 
	t_cmd_list	*next;
};

/* Linked list of commands */

t_cmd_list	*cmd_list_new(void);
t_cmd_list	*cmd_list_last(t_cmd_list *list);
void		cmd_list_append(t_cmd_list **list, t_cmd_list *node);
void		cmd_list_free(t_cmd_list **list);

t_cmd_list	*analyze_lexemes(const char *line);
int	analyze_syntax(t_cmd_list *cmds);

/* Test functions */

void	print_cmds(t_cmd_list *cmds);

#endif
