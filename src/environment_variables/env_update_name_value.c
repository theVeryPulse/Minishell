/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update_name_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:28:18 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 02:51:07 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_env.h"
#include "libft.h"
#include <stdlib.h>

void	env_update_name_value(t_env **stack, const char *name_value)
{
	t_env	*node;
	size_t	i;

	node = *stack;
	while (node)
	{
		i = 0;
		while (node->name_value[i] == name_value[i])
			i++;
		if (i > 0 && node->name_value[i - 1] == '=' && name_value[i - 1] == '=')
		{
			free(node->name_value);
			node->name_value = ft_strdup(name_value);
			return ;
		}
		node = node->next;
	}
	_add_to_env(stack, name_value);
}
