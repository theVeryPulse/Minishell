/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:14:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 20:04:45 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_STATUS_H
# define EXIT_STATUS_H

# define REDIRECT_FILE_PERMISSION_DENIED 1
# define SYNTAX_ERROR_EXIT_STATUS 2
# define IS_A_DIRECTORY_EXIT_STATUS 126
# define PERMISSION_DENIED_EXIT_STATUS 126
# define COMMAND_NOT_FOUND_EXIT_STATUS 127
# define NO_SUCH_FILE_EXIT_STATUS 127
# define SIGINT_EXIT_STATUS 130
# define SIGQUIT_EXIT_STATUS 131

#endif