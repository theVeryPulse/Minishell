/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:08:23 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 17:49:22 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../environment_variables/env.h"

/**
 * @brief Initializes the static minishell struct.
 * 
 * @note This function should not be called again before calling 
 *       minishell_free(), else the pointers to environment variables will be
 *       lost.
 */
extern void	minishell_init(void)
{
	*(minishell()) = (t_minishell){0};
	env_init(&(minishell()->env));
}
