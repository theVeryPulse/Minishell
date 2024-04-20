/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_variable_name_middle.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:21:19 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 14:18:28 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

/**
 * @brief Checks if a character is allowed as the middle character of a variable
 *        name: underscore, digits, letters.
 * 
 * @param c Character to check.
 */
extern bool	is_variable_name_middle(char c)
{
	return (c == '_' || ft_isalnum(c));
}
