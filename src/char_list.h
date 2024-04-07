/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_list.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:34:16 by Philip            #+#    #+#             */
/*   Updated: 2024/04/07 20:43:30 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_char_list	t_char_list;
struct s_char_list
{
	char		c;
	t_char_list	*next;
};

void		char_list_add_char(t_char_list **list, char c);
void		char_list_add_str(t_char_list **list, char *str);
char		*char_list_to_str(t_char_list *list);
void		char_list_free_and_null(t_char_list **list);
