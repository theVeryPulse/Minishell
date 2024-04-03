/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 23:29:59 by Philip            #+#    #+#             */
/*   Updated: 2024/04/03 23:31:16 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	is_redirect(char c)
{
	return (c == '<' || c == '>');
}

// `|`, `<`, or `>`, space, tab, newline
bool	is_metacharacter(char c)
{
	return (c == '<'
			|| c == '>'
			|| c == '|'
			|| c == ' '
			|| c == '\t');
}

bool	is_quotation_mark(char c)
{
	return (c == '\'' || c == '\"');
}
