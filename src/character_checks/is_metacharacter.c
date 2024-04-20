/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_metacharacter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:49:20 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 14:18:19 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

/**
 * @brief Checks if a character is a metacharacter: `|`, `<`, or `>`, space,
 *        tab, and newline
 * 
 * @param c Character to check.
 */
extern bool	is_metacharacter(char c)
{
	return (c == '<'
		|| c == '>'
		|| c == '|'
		|| c == ' '
		|| c == '\t');
}
