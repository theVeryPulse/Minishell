/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:03:31 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 16:49:05 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paths.h"
#include "../environment_variables/t_env.h"
#include "../free/free.h"
#include "libft.h"
#include <unistd.h>

void	search_executable(char **arg, t_env *env)
{
	char	*exe;
	char	**path;
	t_paths	paths;

	paths_init(&paths, env);
	path = paths;
	while (path && *path)
	{
		exe = ft_format_string("%s/%s", *path, *arg);
		if (access(exe, F_OK) == 0)
		{
			free_and_null((void **)arg);
			*arg = exe;
			break ;
		}
		free_and_null((void **)&exe);
		path++;
	}
	paths_free(&paths);
}
