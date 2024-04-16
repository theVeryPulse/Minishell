/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:08:38 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 02:39:22 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "../command_list/cmd_list.h"
#include "../environment_variables/env.h"
#include "../pipes/pipes.h"
#include "../search_executable/search_executable.h"
#include "../free_and_null.h"
#include "../string_array.h"
#include "../get_last_child_exit_status.h"
#include "libft.h"
#include <stddef.h> /* NULL */
#include <stdlib.h> /* exit */
#include <stdio.h> /* printf, perror */
#include <unistd.h> /* execve, fork */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h> /* wait */
#include <readline/readline.h> /* rl_clear_history */

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
int	builtin_env(char **argv, t_env *env, t_cmd_list *cmds, t_pipes *pipes)
{
	t_env	*modified_env;
	char	**arg;

	if (argv[1] == NULL)
	{
		_print_all_environment_variables(env);
		return (0);
	}

	/* create modified environment */
	modified_env = env_copy(env);
	arg = argv + 1;
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
		exit_status = exec_builtin_function(arg, &modified_env, cmds, pipes);
	}
	/* |-- search executable in the new environment */
	else
	{
		has_child_process = true;
		if (!ft_strchr(*arg, '/'))
			search_exec_and_replace_arg(arg, modified_env);
		id = fork();
		if (id == 0)
		{
			char **envp;

			envp = env_build_envp(modified_env);
			if (execve(*arg, arg, envp) == -1)
			{
				ft_dprintf(STDERR_FILENO, "env: ‘%s’: ", *arg);
				perror("");
				free_string_array_and_null(&envp);
				rl_clear_history();
				env_free(&modified_env);
				env_free(&env);
				cmd_list_free(&cmds);
				free(pipes->pipes);
				exit (0);
			}
		}
	}
	env_free(&modified_env);

	if (has_child_process)
	{
		exit_status = get_last_child_exit_status(id);
		if (exit_status != 0)
			exit_status = 127;
	}
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
