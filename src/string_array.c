/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:41:58 by Philip            #+#    #+#             */
/*   Updated: 2024/04/07 02:50:11 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* [ ] Consider merge file with free_and_null() */

#include <stddef.h>
#include <stdlib.h>

/* 
 * free_string_array_and_null() parameter illustration:
 * 
 *        {"a", "b", "c", NULL}
 *          ^    ^    ^   ^
 *          |____|____|___|
 *          |
 *   char **string_array
 *          ^
 *          |
 *  char ***string_array
 * 
*/

void	free_string_array_and_null(char ***string_array)
{
	char	**iterator;

	if (!string_array || !(*string_array))
		return ;
	iterator = *string_array;
	while (iterator && *iterator)
	{
		free(*iterator);
		iterator++;
	}
	free(*string_array);
	*string_array = NULL;
}
