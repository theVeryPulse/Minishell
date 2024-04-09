/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _syntax_analyzer.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 01:23:21 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 11:04:15 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SYNTAX_ANALYZER_H
# define _SYNTAX_ANALYZER_H

/**
 * Internal helper type for `analyze_syntax()`.
 * 
 * @brief Define unexpected characters after redirect symbols
 * 
 */
typedef enum e_type
{
	/* Missing filename/delimiter/command: `>>|` `>|` `<|` `<<|` `|` */
	PIPE,
	/* Missing filename/delimiter: `>>` `>` `<` `<<` */
	NEWLINE,
	/* Missing filename/delimiter: `>>>` `>>>>` `<<>` `<<<<` etc. */
	REDIRECT,
}	t_type;

#endif