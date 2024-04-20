/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_identifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:55:09 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 14:54:41 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../character_checks/character_checks.h" /* is_variable_name_start */
#include <stddef.h> /* size_t */
#include <stdbool.h> /* bool */

/**
 * @brief Checks if an argument is not a valid identifier, which should have
 *        format of `name=value` or `name+=value`.
 * 
 * @param identifier Argument to check
 * @return `true` if identifier is invalid, else `false` 
 * @note 
 * Invalid identifiers include:
 * - a '?' anywhere before '=', e.g. "?=1".
 * - a single '$' as name.
 * - missing name before '=', e.g. "==3".
 * 
 * Special case:
 * - when the name is valid but there is no '=' in the identifier, the whole
 *   identifier is valid but has no effect during minishell's export.
 */
extern bool	is_valid_identifier(const char *identifier)
{
	size_t	i;

	if (!is_variable_name_start(identifier[0]))
		return (false);
	i = 1;
	while (identifier[i] && is_variable_name_middle(identifier[i]))
		i++;
	if (identifier[i] == '\0' || identifier[i] == '='
		|| (identifier[i] == '+' && identifier[i + 1] == '='))
		return (true);
	else
		return (false);
}
