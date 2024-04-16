/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:21:25 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 01:20:26 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cmd_list.h"
#include "libft.h"
#include <stddef.h>

t_cmd_list	*cmd_list_new(void)
{
	t_cmd_list	*new;

	new = (t_cmd_list *)ft_calloc(1, sizeof(t_cmd_list));
	new->should_execute = true;
	return (new);
}
