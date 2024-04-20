/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:43:07 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/20 14:11:55 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../environment_variables/env.h" /* env_update_name_value */
#include "libft.h" /* ft_dprintf */
#include <stdlib.h> /* free */
#include <unistd.h> /* STDERR_FILENO */
#include <stdbool.h> /* bool */

extern int	builtin_export(char **argv, t_env **env);
static bool	_is_append_value_to_name_value(char *name_value);
static void	_append_value_to_name_value(char *name_value, t_env **env);

/**
 * @brief Updates environment variables or adds new ones.
 * 
 * @param env Pointer to the pointer to the stack of environment variables.
 * @param argv Array of strings containing the command arguments.
 * @return 0 if successful, 1 otherwise.
 */
extern int	builtin_export(char **argv, t_env **env)
{
	int		i;
	char	*name_value;
	int		exit_status;

	exit_status = 0;
	if (!argv || !(argv[1]))
		return (exit_status);
	i = 1;
	while (argv[i])
	{
		name_value = argv[i];
		if (!is_valid_identifier(name_value))
		{
			ft_dprintf(STDERR_FILENO, "minishell: export: `%s': not a valid "
				"identifier\n", name_value);
			exit_status = 1;
		}
		else if (_is_append_value_to_name_value(name_value))
			_append_value_to_name_value(name_value, env);
		else if (ft_strchr(name_value, '='))
			env_update_name_value(env, name_value);
		i++;
	}
	return (exit_status);
}

static bool	_is_append_value_to_name_value(char *name_value)
{
	size_t	i;

	i = 0;
	while (name_value[i] && name_value[i] != '+')
		i++;
	if (name_value[i] == '\0')
		return (false);
	else if (name_value[i] == '+' && name_value[i + 1] == '=')
		return (true);
	else
		return (false);
}

static void	_append_value_to_name_value(char *name_value, t_env **env)
{
	char	*name;
	size_t	name_len;
	char	*new_name_value;
	char	*old_value;

	name_len = 0;
	while (name_value[name_len] && name_value[name_len] != '+')
		name_len++;
	name = ft_strndup(name_value, name_len);
	old_value = env_get_value_by_name(*env, name);
	new_name_value = ft_format_string("%s=%s%s", name, old_value,
			&name_value[name_len + 2]);
	env_update_name_value(env, new_name_value);
	free(name);
	free(old_value);
	free(new_name_value);
}
