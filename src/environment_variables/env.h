/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:38:37 by Philip            #+#    #+#             */
/*   Updated: 2024/04/14 17:42:17 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdbool.h>

typedef struct s_env	t_env;
typedef struct s_env
{
	char	*name_value;
	t_env	*next;
}	t_env;

void	env_init(t_env	**env);
void	env_update_name_value(t_env **env, const char *name_value);
char	*env_get_value_by_name(t_env *env, const char *name);
void	env_remove_by_name(t_env **env, const char *name);
char	**env_build_envp(t_env *env);
void	env_free(t_env **env);
t_env	*env_copy(t_env *env);
bool	is_valid_identifier(const char *identifier);

#endif