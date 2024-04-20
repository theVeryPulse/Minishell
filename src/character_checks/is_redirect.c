/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:49:24 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 14:18:25 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

/**
 * @brief Checks if a character is `<` or `>` (denoting redirects)
 * 
 * @param c Character to check.
 */
extern bool	is_redirect(char c)
{
	return (c == '<' || c == '>');
}
