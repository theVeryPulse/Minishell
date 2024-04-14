/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 02:03:18 by Philip            #+#    #+#             */
/*   Updated: 2024/04/14 10:15:36 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdbool.h>

int	builtin_echo(char **argv)
{
	char	**arg;
	bool	no_newline;

	arg = &argv[1];
	no_newline = false;
	while (*arg && ft_strncmp(*arg, "-n", 3) == 0)
	{
		no_newline = true;
		arg++;
	}
	while (arg && *arg)
	{
		if (*arg)
			printf("%s", *arg);
		arg++;
		if (arg && *arg)
			printf(" ");
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
