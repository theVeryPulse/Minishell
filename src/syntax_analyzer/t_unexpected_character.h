/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_unexpected_character.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 01:23:21 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 19:34:09 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_UNEXPECTED_CHARACTER_H
# define T_UNEXPECTED_CHARACTER_H

/**
 * Internal helper type for `analyze_syntax()`.
 * 
 * @brief Define unexpected characters after redirect symbols
 * 
 */
typedef enum e_unexpected_character
{
	/* Missing filename/delimiter/command: `>>|` `>|` `<|` `<<|` `|` */
	PIPE,
	/* Missing filename/delimiter: `>>` `>` `<` `<<` */
	NEWLINE,
	/* Missing filename/delimiter: `>>>` `>>>>` `<<>` `<<<<` etc. */
	REDIRECT,
}	t_unexpected_character;

#endif