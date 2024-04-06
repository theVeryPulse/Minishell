/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_internal.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 01:23:21 by Philip            #+#    #+#             */
/*   Updated: 2024/04/06 01:36:24 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_ANALYZER_INTERNAL_H
# define SYNTAX_ANALYZER_INTERNAL_H

/**
 * Internal helper type for `analyze_syntax()`.
 * 
 * @brief Define unexpected characters after redirect symbols
 * 
 */
typedef enum e_type
{
	/* Missing filename/delimiter: `>>|` `>|` `<|` `<<|` */
	PIPE,
	/* Missing filename/delimiter: `>>` `>` `<` `<<` */
	NEWLINE,
	/* Missing filename/delimiter: `>>>` `>>>>` `<<>` `<<<<` etc. */
	REDIRECT,
}	t_type;

#endif