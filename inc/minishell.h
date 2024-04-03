/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:43:44 by Philip            #+#    #+#             */
/*   Updated: 2024/04/03 20:43:56 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_cmd_list t_cmd_list;

struct s_cmd_list
{
	char		**cmd_argv; // {"echo", "-n", "123", NULL}
	char		**redirects; // {"<infile", "<<delimiter", ">outfile", ">>outfile"}
	t_cmd_list	*next;
};