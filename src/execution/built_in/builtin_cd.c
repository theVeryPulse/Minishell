/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 13:03:40 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/17 14:12:46 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environment_variables/env.h"
#include "../execution/file_check.h"
#include "libft.h"
#include <stdbool.h>
#include <stdio.h> /* printf */
#include <stdlib.h> /* free */
#include <sys/stat.h> /* stat */
#include <unistd.h> /* chdir, getcwd */

#define PATH_MAX 4096

extern int	builtin_cd(char **argv, t_env **env);
static char	*_get_path(char *arg, t_env *env);
static bool	_dir_not_okay(const char *path);;
static void	_update_oldpwd(t_env **env);
static void	_update_pwd(t_env **env);

/**
 * @brief Changes the current working directory.
 * 
 * @param env A pointer to the pointer to the environment variables.
 * @param argv An array of strings containing the command arguments.
 * @return 0 if the operation is successful, 1 otherwise.
 */
extern int	builtin_cd(char **argv, t_env **env)
{
	char	*path;

	if (argv[1] && argv[2])
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
		return (1);
	}
	path = _get_path(argv[1], *env);
	if (_dir_not_okay(path))
	{
		if (path != argv[1])
			free(path);
		return (1);
	}
	_update_oldpwd(env);
	chdir(path);
	_update_pwd(env);
	if (path != argv[1])
		free(path);
	return (0);
}

static char	*_get_path(char *arg, t_env *env)
{
	char	*path;

	if (arg && ft_strncmp(arg, "-", 2) == 0)
	{
		path = env_get_value_by_name(env, "OLDPWD");
		printf("%s\n", path);
	}
	else if (arg)
		path = arg;
	else
		path = env_get_value_by_name(env, "HOME");
	return (path);
}

static bool	_dir_not_okay(const char *path)
{
	t_file_status	status;

	status = file_check(path, CHECK_DIRECTORY);
	if (status == NO_SUCH_FILE_OR_DIRECTORY)
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: cd: no such file or directory: `%s'\n", path);
	}
	else if (status == IS_A_FILE)
		ft_dprintf(STDERR_FILENO, "minishell: cd: %s: Not a directory\n", path);
	else if (status == NO_EXECUTION_PERMISSION)
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: cd: permission denied: `%s'\n", path);
	}
	else if (status == OK)
		return (false);
	return (true);
}

static void	_update_oldpwd(t_env **env)
{
	char		*oldpwd_name_value;
	static bool	first_cd = true;
	char		oldpwd[PATH_MAX];

	getcwd(oldpwd, sizeof(oldpwd));
	if (first_cd)
		first_cd = false;
	else
	{
		oldpwd_name_value = ft_format_string("OLDPWD=%s", oldpwd);
		env_update_name_value(env, oldpwd_name_value);
		free(oldpwd_name_value);
	}
}

static void	_update_pwd(t_env **env)
{
	char	*pwd_name_value;
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	pwd_name_value = ft_format_string("PWD=%s", cwd);
	env_update_name_value(env, pwd_name_value);
	free(pwd_name_value);
}
