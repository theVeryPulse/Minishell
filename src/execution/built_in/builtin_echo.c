/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 02:03:18 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 14:12:11 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> /* printf */
#include <stdbool.h>

extern int	builtin_echo(char **argv);
static bool	_is_flag_for_no_newline(const char *arg);

/**
 * @brief Prints the provided arguments to stdout.
 * 
 * @param argv An array of strings containing the flags and arguments to be 
 *             printed.
 * @return Always returns 0. 
 * @note   Flag: '-' followed by any number of n's.
 */
extern int	builtin_echo(char **argv)
{
	char	**arg;
	bool	no_newline;

	arg = &argv[1];
	no_newline = false;
	while (*arg && _is_flag_for_no_newline(*arg))
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

/**
 * @note valid flag begins with `-` followed by any number of `n`
 */
static bool	_is_flag_for_no_newline(const char *arg)
{
	size_t	i;

	if (!arg)
		return (false);
	i = 0;
	if (arg[i] != '-')
		return (false);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}
