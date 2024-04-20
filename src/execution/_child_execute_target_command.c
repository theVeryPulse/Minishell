/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _child_execute_target_command.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:59:30 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 10:47:26 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell/minishell.h" /* minishell */
#include "../command_list/t_cmd_list.h" /* t_cmd_list */
#include "../environment_variables/env.h" /* env_build_envp */
#include "../exit_status.h" /* exit_status */
#include "../pipes/t_pipes.h" /* t_pipes */
#include "../free/free.h" /*  */
#include "file_check.h" /* file_check */
#include "libft.h" /* ft_dprintf */
#include <unistd.h> /* access, F_OK, STDERR_FILENO, execve */
#include <stdlib.h> /* exit */
#include <readline/readline.h> /* rl_clear_history */

extern void	_child_execute_target_command(t_cmd_list *cmd, t_env *env,
				t_pipes *pipes);
static int	_command_not_found(const char *command);
static int	_is_a_directory(const char *command);

/**
 * @brief Executes the target command. This function exits the process and frees
 *        all dynamically allocated memory, and should only be used in child
 *        processes when pipes are used.
 * 
 * @param cmd A pointer to the command to execute.
 * @param env A pointer to the environment variables
 * @param pipes A pointer to the pipes structure
 */
extern void	_child_execute_target_command(t_cmd_list *cmd, t_env *env,
				t_pipes *pipes)
{
	char	**envp;
	int		exit_status;

	if (!ft_strchr(cmd->argv[0], '/') && access(cmd->argv[0], F_OK) != 0)
		exit_status = _command_not_found(cmd->argv[0]);
	else if (file_check(cmd->argv[0], CHECK_EXECUTABLE) == IS_A_DIRECTORY)
		exit_status = _is_a_directory(cmd->argv[0]);
	else
	{
		envp = env_build_envp(env);
		execve(cmd->argv[0], cmd->argv, envp);
		ft_dprintf(STDERR_FILENO, "minishell: ");
		perror(cmd->argv[0]);
		free_string_array_and_null(&envp);
		exit_status = PERMISSION_DENIED_EXIT_STATUS;
	}
	rl_clear_history();
	if (pipes && pipes->pipes)
		free(pipes->pipes);
	minishell_free();
	exit(exit_status);
}

static int	_command_not_found(const char *command)
{
	ft_dprintf(STDERR_FILENO, "%s: command not found\n", command);
	return (COMMAND_NOT_FOUND_EXIT_STATUS);
}

static int	_is_a_directory(const char *command)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s: Is a directory\n", command);
	return (IS_A_DIRECTORY_EXIT_STATUS);
}