/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _add_to_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:28:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 02:44:14 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

void	_add_to_env(t_env **stack, const char *name_value)
{
	t_env	*new_node;

	new_node = (t_env *)ft_calloc(1, sizeof(t_env));
	new_node->next = NULL;
	if (*stack)
		new_node->next = *stack;
	*stack = new_node;
	new_node->name_value = ft_strdup(name_value);
}
