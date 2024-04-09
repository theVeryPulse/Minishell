/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_redirection_files.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:50:07 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 22:53:39 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_list/cmd_list.h"
#include "character_checks.h"
#include "free_and_null.h"
#include "libft.h"
#include <stddef.h>

/**
 * @brief Set the up redirect files object
 * 
 * @param cmds 
 * @note If any of the redirects has issue, that command will not be executed.
 */
void	set_up_redirect_files(t_cmd_list *cmds)
{
	t_cmd_list	*cmd;
	char		**redirect;
	size_t		i;
	char		*file_path;

	cmd = cmds;
	while (cmd)
	{
		redirect = cmd->redirects;
		while (redirect && *redirect)
		{
			if (ft_strncmp(*redirect, "<<", 2))
			{
				redirect++;
				continue ;
			}
			else
			{
				try_access_file(*redirect);
			}
			redirect++;
		}
		cmd = cmd->next;
	}
}

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
void	try_access_file(const char *redirect)
{
	size_t	i;
	char	*file_path;

	while (is_redirect(redirect[i]))
		i++;
	if (ft_strchr(redirect, '/'))
		file_path = ft_strdup(&redirect[i]);
	else
		file_path = ft_format_string("./%s", &redirect[i]);
	file_path = ft_format_string("./%s", &redirect[i]);
	if (redirect[0] == '<') /* < >> > */
	{
		if (access(file_path, F_OK | O_RDONLY) != 0)
		{
			ft_dprintf(STDERR_FILENO, "minishell: ");
			perror(&redirect[i]);
		}
	}
	else if (redirect[0] == '>')
	{

		if (acesss(file_path, F_OK | O_WRONLY) != 0)
		{
			ft_dprintf(STDERR_FILENO, "minishell: ");
			perror(&redirect[i]);
		}
	}
}
