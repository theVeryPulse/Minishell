/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _replace_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:04:44 by Philip            #+#    #+#             */
/*   Updated: 2024/04/25 19:18:58 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_expand_string.h"
#include "../character_list/char_list.h"
#include "../free/free.h"
#include "libft.h"

extern void	_replace_arg(t_char_list **char_list, char **arg_ptr,
			t_mode mode)
{
	char	*expanded;

	expanded = char_list_to_str(*char_list);
	if (mode == TO_NULL && ft_strlen(expanded) == 0)
		free_and_null((void **)&expanded);
	free_and_null((void **)arg_ptr);
	*arg_ptr = expanded;
	char_list_free_and_null(char_list);
	return ;
}
