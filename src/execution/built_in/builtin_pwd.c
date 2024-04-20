/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:57:10 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/20 14:11:51 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> /* perror */
#include <unistd.h> /* getcwd */

#define PATH_MAX 4096

/**
 * @brief Prints the current working directory.
 *
 * @return 0 upon successful execution, 1 if an error occurs.
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
