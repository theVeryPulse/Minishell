/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:19:20 by Philip            #+#    #+#             */
/*   Updated: 2024/04/07 19:42:42 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_VARIABLES_H
# define ENVIRONMENT_VARIABLES_H

typedef struct s_environ_stack	t_env_stack;
typedef struct s_environ_stack
{
	char		*name_value;
	t_env_stack	*next;
}	t_env_stack;

void	env_build(t_env_stack	**stack);
void	env_update_name_value(t_env_stack **stack, const char *name_value);
char	*env_get_value_by_name(t_env_stack *stack, const char *name);
void	env_remove_by_name(t_env_stack **stack, const char *name);
char	**env_build_envp(t_env_stack *stack);
void	env_free(t_env_stack **stack);

#endif
