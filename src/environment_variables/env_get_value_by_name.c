/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_value_by_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:27:08 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 15:09:42 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_env.h"
#include "libft.h" /* ft_calloc */
#include <stddef.h> /* size_t */

/**
 * @brief Retrieves the value of an environment variable by its name.
 *
 * @param list Pointer to the head of the linked list of environment variables.
 * @param name The name of the environment variable to search for.
 * @return     A duplicate string of the value of the environment variable if
 *             found, or an empty string if the environment variable is not
 *             found. The returned string must be freed by the caller after
 *             use.
 */
extern char	*env_get_value_by_name(t_env *list, const char *name)
{
	t_env	*node;
	size_t	i;

	node = list;
	while (node)
	{
		i = 0;
		while (node->name_value[i] == name[i])
			i++;
		if (node->name_value[i] == '=' && name[i] == '\0')
			return (ft_strdup(&(node->name_value[i + 1])));
		node = node->next;
	}
	return (ft_calloc(1, sizeof(char)));
}
