/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pipes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 20:53:58 by Philip            #+#    #+#             */
/*   Updated: 2024/04/15 20:06:31 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_PIPES_H
# define T_PIPES_H

/**
 * @brief Structure for pipes. `int *pipes` should be a dynamically allocated
 *        array of integers.
 * 
 * @note Pipes is an integer array of length (pipe_count * 2) as each pipe has
 *       two ends.
 */
typedef struct s_pipes
{
	int	*pipes;
	int	pipe_count;
}	t_pipes;

#endif