/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:18:43 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 01:20:42 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CMD_LIST_H
# define T_CMD_LIST_H

# include <stdbool.h>

typedef struct s_cmd_list	t_cmd_list;

struct s_cmd_list
{
	// Null terminated array of arguments
	// Example: `{"echo", "-n", "123", "$VAR$VAR", NULL}`
	char		**cmd_argv;
	// Null terminated array of redirects
	// Example: `{"<infile", "<<delimiter", ">outfile", ">>outfile"}`
	char		**redirects;
	bool		should_execute;
	t_cmd_list	*next;
};

#endif