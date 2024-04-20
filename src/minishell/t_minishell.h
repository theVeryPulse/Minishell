/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:05:13 by Philip            #+#    #+#             */
/*   Updated: 2024/04/19 21:17:24 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MINISHELL_H
# define T_MINISHELL_H

# include "../command_list/t_cmd_list.h"
# include "../environment_variables/t_env.h"
# include <stdbool.h>

typedef enum e_received_signal
{
	NONE = 0,
	RECEIVED_SIGINT,
	RECEIVED_SIGQUIT,
}	t_received_signal;

typedef struct s_minishell
{
	t_cmd_list			*cmds;
	t_env				*env;
	int					exit_status;
	t_received_signal	received_signal;
}	t_minishell;

#endif