/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:08:27 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 17:47:32 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_minishell.h"

/**
 * @brief Returns a pointer to the static minishell struct.
 * 
 * @return `t_minishell*` The static minishell struct. 
 */
extern t_minishell	*minishell(void)
{
	static t_minishell	minishell;

	return (&minishell);
}
