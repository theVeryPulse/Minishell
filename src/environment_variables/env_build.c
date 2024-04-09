/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:27:19 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 02:49:43 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_env.h"
#include <stddef.h>
#include <unistd.h>

void	env_build(t_env **stack)
{
	char	**env_var;

	*stack = NULL;
	env_var = __environ;
	while (env_var && *env_var)
	{
		_add_to_env(stack, *env_var);
		env_var++;
	}
	_add_to_env(stack, "?=0");
}
