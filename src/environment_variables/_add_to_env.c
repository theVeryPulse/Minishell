/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _add_to_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:28:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 01:16:59 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_env.h"
#include "libft.h"

void	_add_to_env(t_env **stack, const char *name_value)
{
	t_env	*new_node;
	t_env	*bottom;

	new_node = (t_env *)ft_calloc(1, sizeof(t_env));
	new_node->next = NULL;
	new_node->name_value = ft_strdup(name_value);
	if (*stack == NULL)
		*stack = new_node;
	else
	{
		bottom = *stack;
		while (bottom->next)
			bottom = bottom->next;
		bottom->next = new_node;
	}
}
