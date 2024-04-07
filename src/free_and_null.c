/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_null.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 02:23:47 by Philip            #+#    #+#             */
/*   Updated: 2024/04/07 02:50:46 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* [ ] Consider merging file with free_string_array_and_null */

#include <stdlib.h>

void	free_and_null(void **ptr)
{
	if (!ptr || !(*ptr))
		return ;
	free(*ptr);
	*ptr = NULL;
}