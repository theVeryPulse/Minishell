/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _execute_shell_script.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:06:18 by Philip            #+#    #+#             */
/*   Updated: 2024/04/18 20:21:29 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../exit_status.h"
#include "../environment_variables/env.h"
#include "libft.h" /* ft_dprintf */
#include <sys/stat.h> /* stat */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* STDERR_FILENO, fork */

void	_execute_shell_script(const char *filepath, t_env **env)
{
	struct stat	statbuf;
	pid_t	id;

	if (stat(filepath, &statbuf) != 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: No such file or directory\n",
			filepath);
		return (env_update_exit_status(env, NO_SUCH_FILE_EXIT_STATUS));
	}
	else if (S_ISDIR(statbuf.st_mode))
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: Is a director\n", filepath);
		return (env_update_exit_status(env, IS_A_DIRECTORY_EXIT_STATUS));
	}
	else if (!(statbuf.st_mode & S_IXUSR) || !(statbuf.st_mode & S_IRUSR))
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: permission denied\n",
			filepath);
		return env_update_exit_status(env, PERMISSION_DENIED_EXIT_STATUS);
	}
	id = fork();
	if (id == 0)
		execute_script_child(filepath);
	env_update_exit_status(env, _exit_status(id));
}
