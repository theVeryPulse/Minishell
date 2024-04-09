/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:07:24 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 10:34:18 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../command_list/cmd_list.h"
#include "../environment_variables/env.h"
#include "../character_list/char_list.h"
#include "../free_and_null.h"
#include "libft.h"
#include <stddef.h>

static char	*_get_var_name(char *str)
{
	size_t	start;
	size_t	end;

	start = 0;
	if (str[start] == '$')
		start++;
	end = start;
	while (str[end] && ft_isalnum(str[end]))
		end++;
	return (ft_strndup(&str[start], end - start));
}

static void	_expand_string(char **arg_ptr, t_env *env)
{
	size_t		i;
	char		*arg;
	t_char_list	*char_list;
	char		*name;
	char		*value;
	char		*expanded;

	char_list = NULL;
	arg = *arg_ptr;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			i++;
			while (arg[i] != '\'')
			{
				char_list_add_char(&char_list, arg[i]);
				i++;
			}
			if (arg[i] == '\'')
				i++;
		}
		else if (arg[i] == '\"')
		{
			i++;
			while (arg[i] != '\"')
			{
				if (arg[i] == '$')
				{
					i++;
					name = _get_var_name(&arg[i]);
					value = env_get_value_by_name(env, name);
					char_list_add_str(&char_list, value);
					free_and_null((void **)&name);
					free_and_null((void **)&value);
					while (arg[i] && ft_isalnum(arg[i]))
						i++;
				}
				else
				{
					char_list_add_char(&char_list, arg[i]);
					i++;
				}
			}
			i++;
		}
		else if (arg[i] == '$')
		{
			name = _get_var_name(&arg[i]);
			value = env_get_value_by_name(env, name);
			char_list_add_str(&char_list, value);
			free_and_null((void **)&name);
			free_and_null((void **)&value);
			i++;
			while (arg[i] && ft_isalnum(arg[i]))
				i++;
		}
		else
		{
			char_list_add_char(&char_list, arg[i++]);
		}
	}
	expanded = char_list_to_str(char_list);
	free_and_null((void **)arg_ptr);
	*arg_ptr = expanded;
	char_list_free_and_null(&char_list);
}

void	expand_arguments(t_cmd_list *cmds, t_env *env)
{
	t_cmd_list	*cmd;
	int			i;

	cmd = cmds;
	while (cmd)
	{
		i = 0;
		while (cmd->cmd_argv && cmd->cmd_argv[i])
		{
			_expand_string(&(cmd->cmd_argv[i]), env);
			i++;
		}
		i = 0;
		while (cmd->redirects && cmd->redirects[i])
		{
			_expand_string(&(cmd->redirects[i]), env);
			i++;
		}
		cmd = cmd->next;
	}
}
