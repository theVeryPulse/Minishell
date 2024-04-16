/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:10:10 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 14:17:06 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include "../command_list/cmd_list.h"
#include "../environment_variables/env.h"

extern void	minishell_free(void)
{
	cmd_list_free(&(minishell()->cmds));
	env_free(&(minishell()->env));
}
