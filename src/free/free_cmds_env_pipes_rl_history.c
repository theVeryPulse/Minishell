/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds_env_pipes_rl_history.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:25:18 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 17:30:12 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_to_free.h"
#include "../command_list/cmd_list.h"
#include "../environment_variables/env.h"
#include <readline/readline.h>
#include <stdlib.h>

/**
 * @brief Frees resources that minishell allocates dynamically: command list,
 *        environment variables, pipes, readline history.
 * 
 * @param to_free The structure that holds pointers to command list, environment
 *                variables, and pipes.
 */
extern void	free_minishell_resources(t_to_free to_free)
{
	if (to_free.cmds)
		cmd_list_free(&(to_free.cmds));
	if (to_free.env)
		env_free(&(to_free.env));
	if (to_free.pipes && to_free.pipes->pipes)
		free(to_free.pipes->pipes);
	rl_clear_history();
}
