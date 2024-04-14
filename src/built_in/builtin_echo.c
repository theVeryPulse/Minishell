/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 02:03:18 by Philip            #+#    #+#             */
/*   Updated: 2024/04/14 02:17:05 by Philip           ###   ########.fr       */
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
	if (ft_strncmp(*arg, "-n", 3) == 0)
	{
		no_newline = true;
		arg++;
	}
	else
		no_newline = false;
	while (arg && *arg)
	{
		if (*arg)
			printf("%s", *arg);
		printf(" ");
		arg++;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
