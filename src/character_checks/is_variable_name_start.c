/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_variable_name_start.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:12:28 by Philip            #+#    #+#             */
/*   Updated: 2024/04/14 11:16:56 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

/**
 * @brief Checks if a character can be a leading character of a variable name
 * 
 * @param c Character to check.
 * @return true if a character is a underscore or letter, else false.
 */
bool	is_variable_name_start(char c)
{
	return (c == '_' || ft_isalpha(c));
}
