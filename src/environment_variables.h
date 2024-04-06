/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:19:20 by Philip            #+#    #+#             */
/*   Updated: 2024/04/06 18:58:25 by Philip           ###   ########.fr       */
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

void	build_env_stack(t_env_stack	**stack);
void	add_to_env(t_env_stack **stack, char *name_value);
char	*find_env_value_by_name(t_env_stack *stack, const char *name);
void	remove_from_env_by_name(t_env_stack **stack, const char *name);
void	free_env_stack(t_env_stack **stack);

#endif
