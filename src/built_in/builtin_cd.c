/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 13:03:40 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/14 01:42:30 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environment_variables/env.h"
#include "libft.h"
#include <unistd.h> /* access, chdir */
#include <stdlib.h> /* free */
#include <stdio.h> /* printf,  */
#include <stdbool.h>

static int	_dir_not_okay(char *path)
{
	int	check;
	
	check = 0;
	if (access(path, F_OK) != 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: no such file or directory: "
				"`%s'\n", path);
		check = -1;
	}
	else if (access(path, X_OK) != 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: permission denied: `%s'\n",
			path);
		check = -1;
	}
	return (check);
}

static char	*_get_cwd(void)
{
	char	cwd[4096];

	getcwd(cwd, sizeof(cwd));
	return (ft_strdup(cwd));
}

int builtin_cd(t_env **env, char **cmd_argv)
{
	char		*path;
	char		*cwd;
	char		*pwd_name_value;
	char		*oldpwd_name_value;
	static bool	first_cd = true;

	if (cmd_argv[1] && cmd_argv[2])
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
		return (1);
	}
	if (cmd_argv[1]
		&& ft_strncmp(cmd_argv[1], "-", 2) == 0)
	{
		path = env_get_value_by_name(*env, "OLDPWD");
		printf("%s\n", path);
	}
	else if (cmd_argv[1])
		path = cmd_argv[1];
	else
		path = env_get_value_by_name(*env, "HOME");
	if (_dir_not_okay(path))
		return (1);
	cwd = _get_cwd();
	chdir(path);
	if (!first_cd)
	{
		oldpwd_name_value = ft_format_string("OLDPWD=%s", cwd);
		env_update_name_value(env, oldpwd_name_value);
		free(oldpwd_name_value);
	}
	if (first_cd)
		first_cd = false;
	if (path != cmd_argv[1])
		free(path);
	free(cwd);
	cwd = _get_cwd();
	pwd_name_value = ft_format_string("PWD=%s", cwd);
	env_update_name_value(env, pwd_name_value);
	free(cwd);
	free(pwd_name_value);
	return (0);
}
