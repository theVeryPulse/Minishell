/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect_files.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:50:07 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 20:19:21 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"
#include "command_list/t_cmd_list.h" /* t_cmd_list */
#include "character_checks/character_checks.h" /* is_redirct */
#include "exit_status.h"
#include "environment_variables/env.h"
#include "libft.h" /* bool, ft_strncmp */
#include <errno.h>
#include <fcntl.h> /* F_OK, O_WRONLY */
#include <stdio.h> /* perror */
#include <stdlib.h> /* free */
#include <unistd.h> /* access */

extern void	check_redirect_files(t_cmd_list *cmds);
static bool	_file_not_okay(const char *redirect);
static bool	_check_file_for_redirect(const char *redirect,
				const char *file_path, const char *arg);

/**
 * @brief Check if files for redirect read/write is accessible. Create the file 
 *        for write if it cannot be found. If any of the redirect files has 
 *        error, set that command's `has_invalid_directs` to true.
 * 
 * @param cmds Command list.
 * @note In line with bash:
 *       Order: from last command to first command, for each command, from first
 *       redirect to last, if any redirect has error, skip the rest redirects.
 */
extern void	check_redirect_files(t_cmd_list *cmds)
{
	t_cmd_list	*cmd;
	char		**redirect;

	cmd = cmds;
	if (cmd->next)
		check_redirect_files(cmd->next);
	redirect = cmd->redirects;
	while (redirect && *redirect)
	{
		if (ft_strncmp(*redirect, "<<", 2) == 0)
		{
			redirect++;
			continue ;
		}
		if (_file_not_okay(*redirect))
		{
			cmd->has_invalid_redirects = true;
			env_update_exit_status(&(minishell()->env),
				REDIRECT_FILE_PERMISSION_DENIED);
			break ;
		}
		redirect++;
	}
}

static bool	_check_file_for_redirect(const char *redirect,
				const char *file_path, const char *arg)
{
	int		fd;
	bool	not_okay;

	not_okay = false;
	if (redirect[0] == '<' && access(file_path, F_OK | R_OK) != 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: ");
		perror(arg);
		not_okay = true;
	}
	else if (redirect[0] == '>')
	{
		fd = open(file_path, O_CREAT | O_WRONLY, 0755);
		if (fd != -1)
			close(fd);
		if (access(file_path, F_OK | O_WRONLY) != 0)
		{
			ft_dprintf(STDERR_FILENO, "minishell: ");
			perror(arg);
			not_okay = true;
		}
	}
	return (not_okay);
}

static bool	_file_not_okay(const char *redirect)
{
	size_t	i;
	char	*file_path;
	bool	not_okay;

	not_okay = false;
	i = 0;
	while (is_redirect(redirect[i]))
		i++;
	if (ft_strchr(redirect, '/'))
		file_path = ft_strdup(&redirect[i]);
	else
		file_path = ft_format_string("./%s", &redirect[i]);
	not_okay = _check_file_for_redirect(redirect, file_path, &redirect[i]);
	free(file_path);
	return (not_okay);
}
