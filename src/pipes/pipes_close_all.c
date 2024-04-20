/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_close_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:50:29 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 19:07:55 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_pipes.h"
#include <unistd.h>

/**
 * @brief Closes all file descriptors in the t_pipes struct.
 * 
 * @param pipes A pointer to a t_pipes structure containing the pipes array.
 */
extern void	pipes_close_all(t_pipes *pipes)
{
	int	i;

	i = 0;
	while (i < pipes->pipe_count * 2)
		close(pipes->pipes[i++]);
}
