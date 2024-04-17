/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:08:38 by Philip            #+#    #+#             */
/*   Updated: 2024/04/17 18:11:40 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "../command_list/t_cmd_list.h"
#include "../environment_variables/env.h" /* env_build_envp */
#include "../pipes/t_pipes.h"
#include "../search_executable/search_executable.h"
#include "../free/free.h"
#include "../execution/execution.h"
#include "libft.h"
#include <stddef.h> /* NULL */
#include <stdlib.h> /* exit */
#include <stdio.h> /* printf, perror */
#include <unistd.h> /* execve, fork */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h> /* wait */
#include <readline/readline.h> /* rl_clear_history */

extern int		builtin_env(char **argv, t_env *env, t_cmd_list *cmds,
					t_pipes *pipes);
static void		_print_env(t_env *env);
static t_env	*_create_modified_env(t_env *env, char **name_value_pairs);
static int		_env_execute_cmd(char **argv, t_env *modified_env,
					t_to_free to_free);
static void		_env_child_free(char ***envp, t_env **modified_env,
					t_to_free to_free);

/**
 * @brief 
 * 
 * @param env 
 * @param argv 
 * @return int 
 * @note
 * - env stops recording variables upon first arg without a '='.
 * - env's exit status is 127 when child's exit code is not 0.
 * - env, cmds, and pipes need to be freed in forked child when execve fails
 */

/**
 * @brief run a program in a modified environment
 * 
 * @param argv arguments starting with "env"
 * @param env environment variable structure
 * @param cmds linked list of commands
 * @param pipes pipes structure (in case of needing free)
 * @return `int` 0 upon success, 127 when target program cannot run correctly.
 */
extern int	builtin_env(char **argv, t_env *env, t_cmd_list *cmds,
	t_pipes *pipes)
{
	t_env	*modified_env;
	char	**arg;
	int		exit_status;

	exit_status = 0;
	if (argv[1] == NULL)
		return (_print_env(env), 0);
	modified_env = _create_modified_env(env, argv + 1);
	arg = argv + 1;
	while (*arg && ft_strchr(*arg, '='))
		arg++;
	if (*arg == NULL)
		return (_print_env(modified_env), env_free(&modified_env), 0);
	if (is_builtin_function(*arg))
		exit_status = execute_builtin_function(arg, &modified_env, cmds, pipes);
	else
	{
		exit_status = _env_execute_cmd(arg, modified_env,
				(t_to_free){.cmds = cmds, .env = env, .pipes = pipes});
	}
	return (env_free(&modified_env), exit_status);
}

static void	_print_env(t_env *env)
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

static t_env	*_create_modified_env(t_env *env, char **name_value_pairs)
{
	t_env	*modified_env;

	modified_env = env_copy(env);
	while (*name_value_pairs && ft_strchr(*name_value_pairs, '='))
	{
		if (is_valid_identifier(*name_value_pairs))
			env_update_name_value(&modified_env, *name_value_pairs);
		name_value_pairs++;
	}
	return (modified_env);
}

static int	_env_execute_cmd(
	char **argv, t_env *modified_env, t_to_free to_free)
{
	char	**envp;
	pid_t	id;
	int		exit_status;

	exit_status = 0;
	if (!ft_strchr(*argv, '/'))
		search_exec_and_replace_arg(argv, modified_env);
	id = fork();
	if (id == 0)
	{
		envp = env_build_envp(modified_env);
		if (execve(*argv, argv, envp) == -1)
		{
			ft_dprintf(STDERR_FILENO, "env: ‘%s’: ", *argv);
			perror("");
			_env_child_free(&envp, &modified_env, to_free);
			exit(127);
		}
	}
	else
		exit_status = get_last_child_exit_status(id);
	if (exit_status != 0)
		exit_status = 127;
	return (exit_status);
}

static void	_env_child_free(char ***envp, t_env **modified_env,
	t_to_free to_free)
{
	free_string_array_and_null(envp);
	env_free(modified_env);
	free_cmds_env_pipes_rl_clear_history(to_free);
}
