/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_list_add_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:11:37 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 10:15:33 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char_list.h"

void	char_list_add_str(t_char_list **list, char *str)
{
	while (*str)
	{
		char_list_add_char(list, *str);
		str++;
	}
}