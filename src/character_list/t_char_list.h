/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_char_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:24:28 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 14:25:50 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CHAR_LIST_H
# define T_CHAR_LIST_H

/**
 * @brief A linked list where each node saves one character.
 * 
 */
typedef struct s_char_list	t_char_list;
struct s_char_list
{
	char		c;
	t_char_list	*next;
};

#endif