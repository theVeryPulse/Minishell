/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_checks.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 23:33:47 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 14:14:08 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_CHECKS_H
# define CHARACTER_CHECKS_H

# include <stdbool.h>

extern bool	is_redirect(char c);
extern bool	is_metacharacter(char c);
extern bool	is_quotation_mark(char c);
extern bool	is_variable_name_start(char c);
extern bool	is_variable_name_middle(char c);

#endif
