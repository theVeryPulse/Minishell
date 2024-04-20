/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update_name_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:28:18 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 15:02:39 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" /* is_valid_identifier */
#include "_env_append.h" /* _env_append */
#include "libft.h" /* ft_strdup */
#include <stdlib.h>

/**
 * @brief Updates the value of an existing environment variable or adds a new 
 *        environment variable.
 *
 * @param list       Pointer to the pointer to the environment variables.
 * @param name_value The name and value of the environment variable to update 
 *                   or add (in the form "name=value").
 */
extern void	env_update_name_value(t_env **list, const char *name_value)
{
	t_env	*node;
	size_t	i;

	if (ft_strncmp(name_value, "?=", 2) != 0
		&& !is_valid_identifier(name_value))
		return ;
	node = *list;
	while (node)
	{
		i = 0;
		while (node->name_value[i]
			&& node->name_value[i] != '='
			&& node->name_value[i] == name_value[i])
			i++;
		if (i > 0 && node->name_value[i] == '=' && name_value[i] == '=')
		{
			free(node->name_value);
			node->name_value = ft_strdup(name_value);
			return ;
		}
		node = node->next;
	}
	_env_append(list, name_value);
}
