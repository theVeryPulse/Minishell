/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _add_argument_and_update_i.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:56:32 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 02:04:34 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_lexical_analyzer.h"
#include "libft.h"

void	_add_argument_and_update_i(
			t_list **arguments, const char *line, size_t *i)
{
	char	*word;
	size_t	i_copy;

	i_copy = *i;
	word = _get_next_word_and_update_i(line, &i_copy);
	ft_lstadd_back(arguments, ft_lstnew((void *)word));
	*i = i_copy;
	// printf("\"%s\" added to list\n", (char *)ft_lstlast(arguments)->content);
}
