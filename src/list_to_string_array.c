/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_string_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:11:35 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 20:19:10 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts a linked list to an string array.
 * 
 * @param list Linked list to convert.
 * @return `char**` String array
 * @note There should only be strings or NULL in the linked list
 */
extern char	**list_to_string_array(t_list *list)
{
	int		list_len;
	int		i;
	char	**string_array;

	if (!list)
		return (NULL);
	list_len = ft_lstsize(list);
	string_array = (char **)ft_calloc(list_len + 1, sizeof(char *));
	i = 0;
	while (i < list_len)
	{
		string_array[i] = (char *)list->content;
		list = list->next;
		i++;
	}
	return (string_array);
}
