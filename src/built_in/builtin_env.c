/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:08:38 by Philip            #+#    #+#             */
/*   Updated: 2024/04/15 00:44:20 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "../environment_variables/env.h"
#include "../is_builtin_function.h"
#include "../free_and_null.h"
#include "libft.h"
#include <stddef.h> /* NULL */
#include <stdio.h> /* printf, */
#include <unistd.h> /* execve,  */


void	_print_all_environment_variables(t_env *env);

/**
 * @brief 
 * 
 * @param env 
 * @param argv 
 * @return int 
 * @note
 * - env stops recording variables upon first arg without a '='.
 * - env's exit status is 127 when child's exit code is not 0.
 */
int	builtin_env(t_env *env, char **argv)
{
	t_env	*modified_env;
	char	**arg;
	char	*path_all;
	char	**paths;
	char	*executable;

	if (argv[1] == NULL)
	{
		_print_all_environment_variables(env);
		return (0);
	}
	modified_env = env_copy(env);
	arg = argv + 1;

	/* create modified environment */
	while (*arg && ft_strchr(*arg, '='))
	{
		if (is_valid_identifier(*arg))
			env_update_name_value(&modified_env, *arg);
		arg++;
	}

	if (*arg == NULL)
	{
		_print_all_environment_variables(modified_env);
		env_free(&modified_env);
		return (0);
	}

	/* execute built-in function */
	int		exit_status;

	if (is_builtin_function(*arg))
	{
		if (ft_strncmp(*arg, "pwd", 4) == 0)
			exit_status =  builtin_pwd();
		else if (ft_strncmp(*arg, "export", 7) == 0)
			exit_status = builtin_export(&modified_env, arg);
		else if (ft_strncmp(*arg, "cd", 3) == 0)
			exit_status = builtin_cd(&modified_env, arg);
		else if (ft_strncmp(*arg, "echo", 5) == 0)
			exit_status = builtin_echo(arg);
		else if (ft_strncmp(*arg, "env", 4) == 0)
			exit_status = builtin_env(modified_env, arg);
	}
	/* search executable in the new environment */
	else
	{
		path_all = env_get_value_by_name(env, "PATH");
		paths = ft_split(path_all, ':');
		free_and_null((void **)&path_all);
		// [ ] search path： search_executable.c:47
	}

	/* prepare argv & envp and fork to execute */
	// execve();

	// [ ] wait for child process to finish (if any)

	env_free(&modified_env);
}

void	_print_all_environment_variables(t_env *env)
{
	t_env	*node;

	node = env;
	while (node)
	{
		if (node->name_value[0] != '?')
			printf("%s\n", node->name_value);
		node = node->next;
	}
}
