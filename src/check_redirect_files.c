/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect_files.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:50:07 by Philip            #+#    #+#             */
/*   Updated: 2024/04/10 19:42:52 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_list/cmd_list.h"
#include "character_checks.h"
#include "free_and_null.h"
#include "libft.h"
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static bool	_file_not_okay(const char *redirect);
static bool	_check_file_for_redirect(const char *redirect,
				const char *file_path, const char *arg);

/**
 * @brief Check if files for redirect read/write is accessible. Create the file 
 *        for write if it cannot be found. If any of the redirect files has 
 *        error, set that command's `should_execute` to false.
 * 
 * @param cmds Head of the command lined list.
 * @note In line with bash:
 *       Order: from last command to first command, for each command, from first
 *       redirect to last, if any redirect has error, skip the rest redirects.
 */
void	check_redirect_files(t_cmd_list *cmds)
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
			cmd->should_execute = false;
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
	if (redirect[0] == '<' && access(file_path, F_OK | O_RDONLY) != 0)
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
	printf("  redirect: checking %s: file okay: %s\n", file_path, not_okay ? "no" : "yes"); /* Test */
	free(file_path);
	return (not_okay);
}