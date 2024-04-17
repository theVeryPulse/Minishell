/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _execute_shell_script.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:06:18 by Philip            #+#    #+#             */
/*   Updated: 2024/04/17 19:09:18 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exit_status.h"
#include <sys/stat.h> /* stat */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* STDERR_FILENO, fork */

int	_execute_shell_script(const char *filepath)
{
	struct stat	statbuf;
	pid_t	id;

	if (stat(filepath, &statbuf) != 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: No such file or directory\n",
			filepath);
		return (NO_SUCH_FILE_EXIT_STATUS);
	}
	else if (S_ISDIR(statbuf.st_mode))
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: Is a director\n", filepath);
		return (IS_A_DIRECTORY_EXIT_STATUS);
	}
	else if (!(statbuf.st_mode & S_IXUSR) || !(statbuf.st_mode & S_IRUSR))
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: permission denied\n",
			filepath);
		return (PERMISSION_DENIED_EXIT_STATUS);
	}
	id = fork();
	if (id == 0)
		execute_script_child(filepath);
	return (get_last_child_exit_status(id));
}
