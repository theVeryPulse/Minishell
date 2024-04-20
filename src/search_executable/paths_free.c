/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:02:15 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 19:16:33 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_paths.h"
#include "../free/free.h"

/**
 * @brief Frees the paths and reset it to NULL.
 * 
 * @param paths Pointer to the paths.
 */
extern void	paths_free(t_paths *paths)
{
	free_string_array_and_null((char ***)paths);
}
