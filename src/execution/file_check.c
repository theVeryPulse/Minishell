/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:09:53 by Philip            #+#    #+#             */
/*   Updated: 2024/04/17 14:01:55 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_check.h"
#include <sys/stat.h> /* stat */
#include "../exit_status.h"

/**
 * @brief 
 * 
 * @param filepath 
 * @param check 
 * @return t_file_status `NO_SUCH_FILE_OR_DIRECTORY`, `IS_A_DIRECTORY`,
 *         `IS_A_FILE`, `NO_EXECUTION_PERMISSION`
 */
extern t_file_status	file_check(const char *filepath, t_check check)
{
	struct stat	statbuf;

	if (stat(filepath, &statbuf) != 0)
		return (NO_SUCH_FILE_OR_DIRECTORY);
	if (check == CHECK_EXECUTABLE)
	{
		if (!S_ISREG(statbuf.st_mode))
			return (IS_A_DIRECTORY);
		if (!(statbuf.st_mode & S_IXUSR))
			return (NO_EXECUTION_PERMISSION);
	}
	else if (check == CHECK_DIRECTORY)
	{
		if (!S_ISDIR(statbuf.st_mode))
			return (IS_A_FILE);
		if (!(statbuf.st_mode & S_IXUSR))
			return (NO_EXECUTION_PERMISSION);
	}
	return (OK);
}
