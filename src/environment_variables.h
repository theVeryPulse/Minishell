/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:19:20 by Philip            #+#    #+#             */
/*   Updated: 2024/04/07 19:46:20 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_VARIABLES_H
# define ENVIRONMENT_VARIABLES_H

typedef struct s_env	t_env;
typedef struct s_env
{
	char	*name_value;
	t_env	*next;
}	t_env;

void	env_build(t_env	**env);
void	env_update_name_value(t_env **env, const char *name_value);
char	*env_get_value_by_name(t_env *env, const char *name);
void	env_remove_by_name(t_env **env, const char *name);
char	**env_build_envp(t_env *env);
void	env_free(t_env **env);

#endif
