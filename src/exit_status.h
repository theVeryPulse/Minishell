/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:14:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/24 02:15:21 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_STATUS_H
# define EXIT_STATUS_H

typedef enum e_exit_status
{
	REDIRECT_FILE_PERMISSION_DENIED = 1,
	SYNTAX_ERROR_EXIT_STATUS = 2,
	IS_A_DIRECTORY_EXIT_STATUS = 126,
	PERMISSION_DENIED_EXIT_STATUS = 126,
	COMMAND_NOT_FOUND_EXIT_STATUS = 127,
	NO_SUCH_FILE_EXIT_STATUS = 127,
	SIGINT_EXIT_STATUS = 130,
	SIGQUIT_EXIT_STATUS = 131,
}	t_exit_status;

#endif