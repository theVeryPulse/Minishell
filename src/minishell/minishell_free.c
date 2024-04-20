/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:10:10 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 17:49:50 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include "../command_list/cmd_list.h"
#include "../environment_variables/env.h"

/**
 * @brief Frees the memory for command list and environment variables.
 */
extern void	minishell_free(void)
{
	cmd_list_free(&(minishell()->cmds));
	env_free(&(minishell()->env));
}
