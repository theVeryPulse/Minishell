/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd .c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuleung <chuleung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:57:10 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/12 21:35:05 by chuleung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

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
int	builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("No such file or directory");
		return (1);
	}
	return (0);
}
