/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 01:19:31 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 19:08:05 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "t_pipes.h"

extern void	pipes_init(t_pipes *pipes, int pipe_count);
extern void	pipes_close_all(t_pipes *pipes);

#endif
