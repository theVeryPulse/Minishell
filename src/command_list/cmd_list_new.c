/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:21:25 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 10:24:02 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_list.h"
#include "libft.h"

t_cmd_list	*cmd_list_new(void)
{
	return ((t_cmd_list *)ft_calloc(1, sizeof(t_cmd_list)));
}
