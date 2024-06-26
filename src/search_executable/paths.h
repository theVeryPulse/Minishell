/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:07:19 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 19:20:39 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATHS_H
# define PATHS_H

# include "t_paths.h"
# include "../environment_variables/t_env.h"

extern void	paths_free(t_paths *paths);
extern void	paths_init(t_paths *paths, t_env *env);

#endif
