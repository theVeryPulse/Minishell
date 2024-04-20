/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_variable_name_start.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:12:28 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 14:18:30 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

/**
 * @brief Checks if a character is allowed as the first character of a variable
 *        name: underscore and letters.
 * 
 * @param c Character to check.
 */
extern bool	is_variable_name_start(char c)
{
	return (c == '_' || ft_isalpha(c));
}
