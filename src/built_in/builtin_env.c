/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:08:38 by Philip            #+#    #+#             */
/*   Updated: 2024/04/15 14:40:44 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "../environment_variables/env.h"
#include "../search_executable/search_executable.h"
#include "../is_builtin_function.h"
#include "../free_and_null.h"
#include "libft.h"
#include <stddef.h> /* NULL */
#include <stdlib.h> /* exit */
#include <stdio.h> /* printf, perror */
#include <unistd.h> /* execve, fork */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h> /* wait */

// [x] env PATH= ls
// [ ] Memory leak: env PATH= ls

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

	/* execution */
	bool	has_child_process;
	int		exit_status;
	pid_t	id;

	exit_status = 0;

	/* |-- execute built-in function */
	if (is_builtin_function(*arg))
	{
		has_child_process = false;
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
	/* |-- search executable in the new environment */
	else
	{
		// [x] search path： search_exec_and_replace_arg_in_cmds.c:47
		if (!ft_strchr(*arg, '/'))
			search_exec_and_replace_arg(arg, modified_env);
		has_child_process = true;
		id = fork();
		if (id == 0)
		{
			// [ ] close pipes?
			if (execve(*arg, arg, env_build_envp(env)) == -1)
			{
				ft_dprintf(STDERR_FILENO, "env: ‘%s’: ", *arg);
				perror("");
				exit (0);
			}
		}
	}

	// [x] wait for child process to finish (if any)
	int	wstatus;
	int child_exit_status;

	if (has_child_process)
	{
		// [ ] same code with execute_cmds: 276
		waitpid(id, &wstatus, 0);
		if (WIFEXITED(wstatus))
			child_exit_status = WEXITSTATUS(wstatus);
		if (child_exit_status == 0)
			return (0);
		else
			return (127);
	}
	env_free(&modified_env);
	return (exit_status);
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
