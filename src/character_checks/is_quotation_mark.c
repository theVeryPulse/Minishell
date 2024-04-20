/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quotation_mark.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:49:22 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 14:18:22 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

/**
 * @brief Checks if a character is either `'` or `"`.
 * 
 * @param c Character to check.
 */
extern bool	is_quotation_mark(char c)
{
	return (c == '\'' || c == '\"');
}
