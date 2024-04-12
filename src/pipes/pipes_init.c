/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:49:09 by Philip            #+#    #+#             */
/*   Updated: 2024/04/12 21:20:20 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_t_pipe.h"
#include "libft.h"
#include <unistd.h>

/**
 * @brief Initializes a t_pipes structure with the specified number of pipes.
 * 
 * @param pipes A pointer to the t_pipes structure to initialize.
 * @param pipe_count The number of pipes to create.
 */
void	pipes_init(t_pipes *pipes, int pipe_count)
{
	int	i;

	if (pipe_count < 1)
	{
		pipes->pipe_count = 0;
		pipes->pipes = NULL;
		return ;
	}
	pipes->pipe_count = pipe_count;
	pipes->pipes = (int *)ft_calloc(pipe_count * 2, sizeof(int));
	i = 0;
	while (i < pipe_count * 2)
	{
		pipe(&(pipes->pipes[i]));
		i += 2;
	}
}
