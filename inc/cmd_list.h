/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:23:53 by Philip            #+#    #+#             */
/*   Updated: 2024/04/06 16:52:13 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LIST_H
# define CMD_LIST_H

typedef struct s_cmd_list	t_cmd_list;

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

#endif