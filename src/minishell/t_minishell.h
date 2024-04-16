/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:05:13 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 14:06:36 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MINISHELL_H
# define T_MINISHELL_H

# include "../command_list/t_cmd_list.h"
# include "../environment_variables/t_env.h"

typedef struct s_minishell
{
	t_cmd_list	*cmds;
	t_env		*env;
}	t_minishell;

#endif