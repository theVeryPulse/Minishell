/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _execute_builtin_function.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:59:40 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 17:07:06 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in/built_in.h"
#include "../pipes/t_pipes.h" /* t_pipes */
#include "libft.h" /* ft_strncmp */

/**
 * @brief Executes the built-in function. This function does not exit the
 *        process or frees command list or environment variables.
 * 
 * @param argv Arguments for the function.
 * @param env Pointer to the pointer to the environment variables.
 * @param cmds The complete command list for free before a child process exits.
 * @param pipes Pointer to the pipes struct which may need to be freed.
 * @return `int` the exit status of target built-in function.
 */
extern int	_execute_builtin_function(char **argv, t_env **env,
	t_cmd_list *cmds, t_pipes *pipes)
{
	int	exit_status;

	exit_status = 0;
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		exit_status = builtin_cd(argv, env);
	else if (ft_strncmp(argv[0], "pwd", 4) == 0)
		exit_status = builtin_pwd();
	else if (ft_strncmp(argv[0], "env", 4) == 0)
		exit_status = builtin_env(argv, *env, cmds, pipes);
	else if (ft_strncmp(argv[0], "echo", 5) == 0)
		exit_status = builtin_echo(argv);
	else if (ft_strncmp(argv[0], "exit", 5) == 0)
		builtin_exit(argv, *env, cmds, pipes);
	else if (ft_strncmp(argv[0], "unset", 6) == 0)
		builtin_unset(argv, env);
	else if (ft_strncmp(argv[0], "export", 7) == 0)
		exit_status = builtin_export(argv, env);
	return (exit_status);
}
