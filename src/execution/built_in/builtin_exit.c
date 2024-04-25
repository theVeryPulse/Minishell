/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:39:37 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/25 23:07:26 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_exit_err.h"
#include "../../minishell/minishell.h" /* minishell */
#include "../../free/free.h" /* free_cmds_env_pipes_rl_clear_history */
#include "../../environment_variables/t_env.h" /* t_env */
#include "../../command_list/t_cmd_list.h" /* t_cmd_list */
#include "../../pipes/t_pipes.h" /* t_pipes */
#include "libft.h"
#include <stdbool.h>
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit, free */
#include <unistd.h> /* STDERR_FILENO */

extern void	builtin_exit(char **argv, t_env *env, t_cmd_list *cmds,
				t_pipes *pipes);
static bool	_is_a_number(char *str);
static void	_exit_error_handle(char *arg, t_to_free to_free,
				t_exit_err err_case);
static int	_calculate_exit_status(char *c);

/**
 * @brief Exits the shell with a specified exit status or the latest recorded
 *        exit status.
 * 
 * @param argv Array of strings containing the command arguments.
 * @param env Pointer to the environment variables.
 * @param cmds Pointer to the commands.
 * @param pipes Pointer to the pipes structure.
 */
extern void	builtin_exit(char **argv, t_env *env, t_cmd_list *cmds,
			t_pipes *pipes)
{
	int			exit_status;
	t_to_free	to_free;

	printf("exit\n");
	exit_status = 0;
	to_free = (t_to_free){.cmds = cmds, .env = env, .pipes = pipes};
	if (argv[1])
	{
		if (_is_a_number(argv[1]) == false)
			_exit_error_handle(argv[1], to_free, NUMERIC);
		exit_status = _calculate_exit_status(argv[1]);
		if (argv[2])
			_exit_error_handle(argv[1], to_free, MANY_ARGS);
		if (exit_status < 0 || exit_status > 255)
			_exit_error_handle(argv[1], to_free, NUMERIC);
		free_minishell_resources(to_free);
		exit(exit_status);
	}
	free_minishell_resources(to_free);
	exit(minishell()->exit_status);
}

static bool	_is_a_number(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

static void	_exit_error_handle(char *arg, t_to_free to_free,
				t_exit_err err_case)
{
	if (err_case == NUMERIC)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: %s: numeric argument "
			"required\n", arg);
		free_minishell_resources(to_free);
		exit(2);
	}
	else if (err_case == MANY_ARGS)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		free_minishell_resources(to_free);
		exit(1);
	}
}

static int	_calculate_exit_status(char *c)
{
	long long	value_aft_atoi;

	value_aft_atoi = ft_atoi(c);
	value_aft_atoi %= 256;
	if (value_aft_atoi < 0)
		value_aft_atoi += 256;
	return ((int)value_aft_atoi);
}
