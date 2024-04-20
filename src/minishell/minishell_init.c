/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:08:23 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 11:04:08 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../environment_variables/env.h"

extern void	minishell_init(void)
{
	*(minishell()) = (t_minishell){0};
	env_init(&(minishell()->env));
}
