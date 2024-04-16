/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:02:15 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 16:12:04 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_paths.h"
#include "../free/free.h"

void	paths_free(t_paths *paths)
{
	free_string_array_and_null((char ***)paths);
}
