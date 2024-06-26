/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:02:17 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 19:17:38 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_paths.h"
#include "../environment_variables/env.h"
#include "../free/free.h"
#include "libft.h"

/**
 * @brief Initializes the paths from envrionment variables.
 * 
 * @param paths Pointer to the paths to save paths.
 * @param env Environment variables
 */
extern void	paths_init(t_paths *paths, t_env *env)
{
	char	*path_all;

	path_all = env_get_value_by_name(env, "PATH");
	*paths = (t_paths)ft_split(path_all, ':');
	free_and_null((void **)&path_all);
}
