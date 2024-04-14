/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_list_to_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:10:41 by Philip            #+#    #+#             */
/*   Updated: 2024/04/14 12:01:26 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char_list.h"
#include "libft.h"
#include <stddef.h>

char	*char_list_to_str(t_char_list *list)
{
	size_t		len;
	size_t		i;
	t_char_list	*node;
	char		*str;

	if (!list)
		return (ft_calloc(1, sizeof(char)));
	node = list;
	len = 0;
	while (node)
	{
		if (node->c != '\0')
			len++;
		node = node->next;
	}
	str = (char *)ft_calloc(len + 1, sizeof(char));
	node = list;
	i = 0;
	while (node)
	{
		if (node->c != '\0')
			str[i++] = node->c;
		node = node->next;
	}
	return (str);
}
