/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:31:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 00:44:35 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_execution.h"
#include "../minishell/minishell.h"
#include "../command_list/cmd_list.h" /* cmd_list_len */
#include "../environment_variables/t_env.h" /* t_env */
#include "libft.h"

extern void	execute_commands(t_cmd_list *cmds, t_env **env);
static bool	_is_shell_script(const char **argv);

extern void	execute_commands(t_cmd_list *cmds, t_env **env)
{
	if (_is_shell_script((const char **)cmds->argv))
		_execute_shell_script(cmds->argv[0], env);
	else if (cmd_list_len(cmds) == 1)
		_execute_one_command(cmds, env);
	else
		_execute_multiple_commands(cmds, env);
	minishell()->received_signal = NONE;
}

static bool	_is_shell_script(const char **argv)
{
	return (argv
		&& argv[0]
		&& ft_strchr(argv[0], '/')
		&& ft_strlen(argv[0]) > 2
		&& ft_strncmp(ft_strchr(argv[0], '\0') - 3, ".sh", 3) == 0);
}
