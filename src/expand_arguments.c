/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:07:24 by Philip            #+#    #+#             */
/*   Updated: 2024/04/07 20:40:29 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_list.h"
#include "environment_variables.h"
#include "char_list.h"
#include "free_and_null.h"
#include "libft.h"
#include <stddef.h>

/* [ ] echo $USER'$USER'"$USER" -> SIGSEGV */

static char	*get_var_name(char *str)
{
	size_t	start;
	size_t	end;

	start = 0;
	if (str[start] == '$')
		start++;
	end = start;
	while (str[end] && str[end] != ' ' && str[end] != '\"')
		end++;
	return (ft_strndup(&str[start], end - start));
}

static void	expand_string(char **arg_ptr, t_env *env)
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
		if (arg[i] == '\'') /*  '123'  , oldlen:5, newlen:3 */
		{                   /* ~34567~                      */
			i++;
			while (arg[i] != '\'')
			{
				char_list_add_char(&char_list, arg[i]);
				i++;
			}
		}
		else if (arg[i] == '\"')
		{
			i++;
			while (arg[i] != '\"')
			{
				if (arg[i] == '$')
				{
					name = get_var_name(&arg[i]);
					value = env_get_value_by_name(env, name);
					char_list_add_str(&char_list, value);
					free_and_null((void **)&name);
					free_and_null((void **)&value);
					while (arg[i] && arg[i] != ' ' && arg[i] != '\"')
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
			name = get_var_name(&arg[i]);
			value = env_get_value_by_name(env, name);
			char_list_add_str(&char_list, value);
			free_and_null((void **)&name);
			free_and_null((void **)&value);
			while (arg[i] && arg[i] != ' ' && arg[i] != '\"')
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
		while (cmd->cmd_argv[i])
		{
			expand_string(&(cmd->cmd_argv[i]), env);
			i++;
		}
		cmd = cmd->next;
	}
}