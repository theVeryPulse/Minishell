/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_list.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:34:16 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 14:25:21 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAR_LIST_H
# define CHAR_LIST_H

# include "t_char_list.h"

extern void	char_list_add_char(t_char_list **list, char c);
extern void	char_list_add_str(t_char_list **list, char *str);
extern char	*char_list_to_str(t_char_list *list);
extern void	char_list_free_and_null(t_char_list **list);

#endif
