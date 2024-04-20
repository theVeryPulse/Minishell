/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _is_variable_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 02:03:59 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 02:06:50 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../character_checks/character_checks.h"
#include <stdbool.h>
#include <stddef.h>

extern bool	_is_variable_name(char *arg)
{
	size_t	i;

	if (arg[0] != '$' || !is_variable_name_start(arg[1]))
		return (false);
	i = 2;
	while (is_variable_name_middle(arg[i]))
		i++;
	return (arg[i] == '\0');
}
