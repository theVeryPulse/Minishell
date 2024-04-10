/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_value_by_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:27:08 by Philip            #+#    #+#             */
/*   Updated: 2024/04/10 01:29:02 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stddef.h>

/**
 * @brief Retrieves the value of an environment variable by its name.
 *
 * @param stack A pointer to the head of the linked list of environment 
 *              variables.
 * @param name  The name of the environment variable to search for.
 * @return      A duplicate string of the value of the environment variable if
 *              found, or NULL if the environment variable is not found.
 *              The returned string should be freed by the caller after use.
 */
char	*env_get_value_by_name(t_env *stack, const char *name)
{
	t_env	*node;
	size_t	i;

	node = stack;
	while (node)
	{
		i = 0;
		while (node->name_value[i] == name[i])
			i++;
		if (node->name_value[i] == '=' && name[i] == '\0')
			return (ft_strdup(&(node->name_value[i + 1])));
		node = node->next;
	}
	return (NULL);
}
