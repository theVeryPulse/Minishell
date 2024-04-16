/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:38:37 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 16:43:33 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "t_env.h"
# include <stdbool.h>

extern void		env_init(t_env	**env);
extern void		env_update_name_value(t_env **env, const char *name_value);
extern char		*env_get_value_by_name(t_env *env, const char *name);
extern void		env_remove_by_name(t_env **env, const char *name);
extern char		**env_build_envp(t_env *env);
extern void		env_free(t_env **env);
extern t_env	*env_copy(t_env *env);
extern bool		is_valid_identifier(const char *identifier);
extern void		env_update_exit_status(t_env **env, int exit_status);

#endif