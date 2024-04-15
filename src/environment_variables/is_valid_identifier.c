/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_identifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:55:09 by Philip            #+#    #+#             */
/*   Updated: 2024/04/14 17:42:06 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../character_checks/character_checks.h"
#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Checks if an argument is not a valid identifier, in the format of
 *        `name=value`
 * 
 * @param identifier Argument to check
 * @return `true` if identifier is invalid, else `false` 
 * @note 
 * Invalid identifiers include:
 * - a '?' anywhere before '=', e.g. "?=1"
 * - a '$' 
 * - no name before '=', e.g. "==3"
 * 
 * Special case:
 * - when there is no '=' in the identifier, it is valid but has no effect
 */
bool	is_valid_identifier(const char *identifier)
{
	size_t	i;

	if (!is_variable_name_start(identifier[0]))
		return (false);
	i = 1;
	while (identifier[i] && is_variable_name_middle(identifier[i]))
		i++;
	if (identifier[i] != '=' && identifier[i] != '\0')
		return (false);
	else
		return (true);
}
