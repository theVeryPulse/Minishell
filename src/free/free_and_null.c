/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_null.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 02:23:47 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 17:27:27 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * @brief Frees the memory pointed by a pointer, then reset this pointer to
 *        NULL.
 * 
 * @param ptr Pointer to the pointer to the memory to free.
 */
extern void	free_and_null(void **ptr)
{
	if (!ptr || !(*ptr))
		return ;
	free(*ptr);
	*ptr = NULL;
}
