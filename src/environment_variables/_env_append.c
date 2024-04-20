/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:28:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 15:01:30 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_env.h"
#include "libft.h" /* ft_strdup, ft_calloc */

/**
 * @brief Appends the name-value string to environment variables. This function
 *        does not check if the variable already exists. env_update_name_value
 *        should be used instead if it is unkown if a variable already exits.
 * 
 * @param list Pointer to the pointer to the environment variables.
 * @param name_value The name-value string to add.
 */
extern void	_env_append(t_env **list, const char *name_value)
{
	t_env	*new_node;
	t_env	*bottom;

	new_node = (t_env *)ft_calloc(1, sizeof(t_env));
	new_node->next = NULL;
	new_node->name_value = ft_strdup(name_value);
	if (*list == NULL)
		*list = new_node;
	else
	{
		bottom = *list;
		while (bottom->next)
			bottom = bottom->next;
		bottom->next = new_node;
	}
}
