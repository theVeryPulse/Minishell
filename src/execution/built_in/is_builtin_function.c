/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:26:43 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 16:34:25 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

/* 
|command |options                                |
| ------ | ------------------------------------- |
| echo   | -n                                    |
| cd     | with only a relative or absolute path |
| pwd    | no options                            |
| export | no options                            |
| unset  | no options                            |
| env    | no options or arguments               |
| exit   | no options                            |
*/

/**
 * @brief Checks if a command is a built-in function
 * 
 * @param cmd Command to check
 * @return `bool`
 * @note `echo` `cd` `pwd` `export` `unset` `env` `exit`
 */
extern bool	is_builtin_function(const char *cmd)
{
	return (ft_strncmp("cd", cmd, 3) == 0
		|| ft_strncmp("env", cmd, 4) == 0
		|| ft_strncmp("pwd", cmd, 4) == 0
		|| ft_strncmp("echo", cmd, 5) == 0
		|| ft_strncmp("exit", cmd, 5) == 0
		|| ft_strncmp("unset", cmd, 6) == 0
		|| ft_strncmp("export", cmd, 7) == 0);
}
