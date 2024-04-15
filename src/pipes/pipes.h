/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 01:19:31 by Philip            #+#    #+#             */
/*   Updated: 2024/04/15 20:10:47 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "t_pipes.h"

void	pipes_init(t_pipes *pipes, int pipe_count);
void	pipes_close_all(t_pipes *pipes);

#endif
