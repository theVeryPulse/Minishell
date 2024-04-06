/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:19:20 by Philip            #+#    #+#             */
/*   Updated: 2024/04/06 19:52:10 by Philip           ###   ########.fr       */
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

#endif
