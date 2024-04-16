/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:08:27 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 14:12:15 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_minishell.h"

extern t_minishell	*minishell(void)
{
	static t_minishell	minishell;

	return (&minishell);
}
