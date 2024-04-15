/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:39:37 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/15 20:44:33 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_t_exit_err.h"
#include "_t_to_free.h"
#include "../environment_variables/env.h"
#include "../command_list/cmd_list.h"
#include "../pipes/pipes.h"
#include "libft.h"
#include <stdlib.h> /* exit, free */
#include <unistd.h> /* STDERR_FILENO */
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

static bool	_is_a_number(char *fir_arg);
static void	_exit_error_handle(char *arg, t_to_free to_free,
				t_exit_err err_case);
static int	_calc_exit_status(char *c);
static void	_exit_free(t_to_free to_free);

/**
 * @brief Exits the shell with a specified exit status or the default status.
 * This function exits the shell with a specified exit status if provided as a
 * command argument. If no argument is provided, the shell exits with the 
 * default status of 0.
 * 
 * @param cmd_argv An array of strings containing the command arguments.
 * @param env A pointer to the environment variables.
 * @param cmds A pointer to the command list.
 * @param pipes A pointer to the pipes structure.
 */
void	builtin_exit(char **cmd_argv, t_env *env, t_cmd_list *cmds,
			t_pipes *pipes)
{
	int			exit_status;
	t_to_free	to_free;

	exit_status = 0;
	to_free = (t_to_free){.cmds = cmds, .env = env, .pipes = pipes};
	if (cmd_argv[1])
	{
		if (_is_a_number(cmd_argv[1]) == false)
			_exit_error_handle(cmd_argv[1], to_free, NUMERIC);
		exit_status = _calc_exit_status(cmd_argv[1]);
		if (cmd_argv[2])
			_exit_error_handle(cmd_argv[1], to_free, MANY_ARGS);
		if (exit_status < 0 || exit_status > 255)
			_exit_error_handle(cmd_argv[1], to_free, NUMERIC);
		_exit_free(to_free);
		exit(exit_status);
	}
	_exit_free(to_free);
	exit(0);
}

static bool	_is_a_number(char *fir_arg)
{
	if (*fir_arg != '-' || *fir_arg != '+')
		fir_arg++;
	while (*fir_arg)
	{
		if (!ft_isdigit(*fir_arg))
			return (false);
		fir_arg++;
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
		_exit_free(to_free);
		exit(2);
	}
	else if (err_case == MANY_ARGS)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		_exit_free(to_free);
		exit(1);
	}
}

static int	_calc_exit_status(char *c)
{
	long long	value_aft_atoi;

	value_aft_atoi = ft_atoi(c);
	value_aft_atoi %= 256;
	if (value_aft_atoi < 0)
		value_aft_atoi += 256;
	return ((int)value_aft_atoi);
}

static void	_exit_free(t_to_free to_free)
{
	env_free(&(to_free.env));
	cmd_list_free(&(to_free.cmds));
	free(to_free.pipes->pipes);
	rl_clear_history();
}
