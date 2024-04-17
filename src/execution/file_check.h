/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:40:37 by Philip            #+#    #+#             */
/*   Updated: 2024/04/17 14:03:50 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_CHECK_H
# define FILE_CHECK_H

typedef enum	e_file_status
{
	NO_SUCH_FILE_OR_DIRECTORY,
	IS_A_DIRECTORY,
	IS_A_FILE,
	NO_EXECUTION_PERMISSION,
	OK = 0,
}	t_file_status;

typedef enum	e_check
{
	CHECK_EXECUTABLE,
	CHECK_FILE,
	CHECK_DIRECTORY
}	t_check;

extern t_file_status	file_check(const char *filepath, t_check check);

#endif