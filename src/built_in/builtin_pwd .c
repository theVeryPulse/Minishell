/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd .c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:57:10 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/16 16:34:08 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <limits.h>

#define PATH_MAX 4096

/**
 * @brief Prints the current working directory.
 *
 * This function retrieves the current working directory and prints it to stdout.
 *
 * @return 0 upon successful execution, 1 if an error occurs.
 * 
 * @note This function relies on the getcwd() system call.
 */
extern int	builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("minishell");
		return (1);
	}
	return (0);
}
