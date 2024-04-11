/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 01:19:31 by Philip            #+#    #+#             */
/*   Updated: 2024/04/11 11:08:29 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Structure for pipes
 * 
 * @note Pipes is an integer array of length (pipe_count * 2) as each pipe has
 *       two ends.
 */
typedef struct s_pipes
{
	int	*pipes;
	int	pipe_count;
}	t_pipes;
