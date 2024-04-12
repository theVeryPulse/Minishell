/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:49:09 by Philip            #+#    #+#             */
/*   Updated: 2024/04/12 20:57:23 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_t_pipe.h"
#include "libft.h"
#include <unistd.h>

/**
 * @brief Set the up pipes object
 * 
 * @param cmds 
 * @return int* 
 * @note 
 * 
 * cmd_count 3
 * pipes = [0] [1] [2] [3] [4] [5]
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
