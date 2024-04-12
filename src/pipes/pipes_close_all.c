/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_close_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:50:29 by Philip            #+#    #+#             */
/*   Updated: 2024/04/12 20:55:49 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_t_pipe.h"
#include <unistd.h>

void	pipes_close_all(t_pipes *pipes)
{
	int	i;
	
	i = 0;
	while (i < pipes->pipe_count * 2)
		close(pipes->pipes[i++]);
}
