/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuleung <chuleung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:39:37 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/14 22:23:53 by chuleung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_t_exit_err.h"
#include "../environment_variables/env.h"
#include "../command_list/cmd_list.h"
#include "../pipes/pipes.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <limits.h>

int	_calc_exit_status(char *c)
{
	long long	value_aft_atoi;

	value_aft_atoi = ft_atoi(c);
	value_aft_atoi %= 256;
	if (value_aft_atoi < 0)
		value_aft_atoi += 256;
	return ((int)value_aft_atoi);
}

void	_exit_free(t_env **env, t_cmd_list *cmds, t_pipes *pipes)
{
	env_free(env);
	cmd_list_free(&cmds);
	free(pipes->pipes);
	rl_clear_history();
}

void	_exit_error_handle(char *arg, t_env **env, t_cmd_list *cmds,
			t_pipes *pipes, t_exit_err err_case)
{
	if (err_case == NUMERIC)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: %s: numeric argument "
			"required\n", arg);
		_exit_free(env, cmds, pipes);
		exit(2);
	}
	else if (err_case == MANY_ARGS)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		_exit_free(env, cmds, pipes);
		exit(1);
	}
}

bool	_is_valid_integer(char *fir_arg)
{
	if (*fir_arg != '-' || *fir_arg != '+')
			fir_arg++;
	while (*fir_arg)
	{
		if (*fir_arg < '0' || *fir_arg > '9')
			return (false);
		fir_arg++;
	}
	return (true);
}

void	builtin_exit(char **cmd_argv, t_env **env, t_cmd_list *cmds,
			t_pipes *pipes)
{
	int	exit_status = 0;

	if (cmd_argv[1] != NULL)
	{
		if (_is_valid_integer(cmd_argv[1]) == false)
			_exit_error_handle(cmd_argv[1], env, cmds, pipes, NUMERIC);
		exit_status = _calc_exit_status(cmd_argv[1]);
		if (cmd_argv[2] != NULL)
			_exit_error_handle(cmd_argv[1], env, cmds, pipes, MANY_ARGS);
		if (exit_status < 0 || exit_status > 255)
			_exit_error_handle(cmd_argv[1], env, cmds, pipes, NUMERIC);
		_exit_free(env, cmds, pipes);
		exit(exit_status);
	}
	_exit_free(env, cmds, pipes);
	exit(0);
}
