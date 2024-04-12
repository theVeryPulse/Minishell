/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _expand_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:55:56 by Philip            #+#    #+#             */
/*   Updated: 2024/04/12 23:57:46 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../command_list/cmd_list.h"
#include "../character_list/char_list.h"
#include "../environment_variables/env.h"
#include "../free_and_null.h"
#include "libft.h"
#include <stddef.h>

static void	_add_literal_str(t_char_list **char_list, const char *arg,
				size_t *i);
static void	_add_env_expanded_str(t_char_list **char_list, const char *arg,
				size_t *i, t_env *env);
static void	_add_env_value(t_char_list **char_list, const char *arg,
				size_t *i, t_env *env);
static char	*_get_var_name(const char *str);

void	_expand_string(char **arg_ptr, t_env *env)
{
	size_t		i;
	char		*arg;
	t_char_list	*char_list;
	char		*expanded;

	char_list = NULL;
	arg = *arg_ptr;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
			_add_literal_str(&char_list, arg, &i);
		else if (arg[i] == '\"')
			_add_env_expanded_str(&char_list, arg, &i, env);
		else if (arg[i] == '$')
			_add_env_value(&char_list, arg, &i, env);
		else
			char_list_add_char(&char_list, arg[i++]);
	}
	expanded = char_list_to_str(char_list);
	free_and_null((void **)arg_ptr);
	*arg_ptr = expanded;
	char_list_free_and_null(&char_list);
}

static void	_add_literal_str(t_char_list **char_list, const char *arg,
				size_t *i)
{
	(*i)++;
	while (arg[*i] != '\'')
	{
		char_list_add_char(char_list, arg[*i]);
		(*i)++;
	}
	if (arg[*i] == '\'')
		(*i)++;
}

static void	_add_env_expanded_str(t_char_list **char_list, const char *arg,
				size_t *i, t_env *env)
{
	char	*name;
	char	*value;

	(*i)++;
	while (arg[*i] != '\"')
	{
		if (arg[*i] == '$')
		{
			(*i)++;
			name = _get_var_name(&arg[*i]);
			value = env_get_value_by_name(env, name);
			char_list_add_str(char_list, value);
			free_and_null((void **)&name);
			free_and_null((void **)&value);
			while (arg[*i] && ft_isalnum(arg[*i]))
				(*i)++;
		}
		else
		{
			char_list_add_char(char_list, arg[*i]);
			(*i)++;
		}
	}
	(*i)++;
}

static void	_add_env_value(t_char_list **char_list, const char *arg,
				size_t *i, t_env *env)
{
	char	*name;
	char	*value;

	name = _get_var_name(&arg[*i]);
	value = env_get_value_by_name(env, name);
	char_list_add_str(char_list, value);
	free_and_null((void **)&name);
	free_and_null((void **)&value);
	if (ft_strncmp(&arg[*i], "$?", 2))
	{
		(*i) += 2;
		return ;
	}
	(*i)++;
	while (arg[*i] && ft_isalnum(arg[*i]))
		(*i)++;
}

static char	*_get_var_name(const char *str)
{
	size_t	start;
	size_t	end;

	if (ft_strncmp(str, "$?", 3) == 0)
		return (ft_strdup("?"));
	start = 0;
	if (str[start] == '$')
		start++;
	end = start;
	while (str[end] && ft_isalnum(str[end]))
		end++;
	return (ft_strndup(&str[start], end - start));
}
