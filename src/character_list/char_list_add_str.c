/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_list_add_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:11:37 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 14:30:08 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char_list.h"

/**
 * @brief Adds all characters of a string to the character list.
 * 
 * @param list Pointer to the pointer to the character list.
 * @param str String providing characters to add.
 */
void	char_list_add_str(t_char_list **list, char *str)
{
	if (!str)
		return ;
	if (*str == '\0')
		char_list_add_char(list, *str);
	while (*str)
	{
		char_list_add_char(list, *str);
		str++;
	}
}
