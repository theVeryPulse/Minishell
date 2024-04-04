/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_checks.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 23:33:47 by Philip            #+#    #+#             */
/*   Updated: 2024/04/04 18:57:52 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_CHECKS_H
# define CHARACTER_CHECKS_H
# include <stdbool.h>

bool	is_redirect(char c);
bool	is_metacharacter(char c);
bool	is_quotation_mark(char c);
#endif
