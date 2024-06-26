/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _expand_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:55:56 by Philip            #+#    #+#             */
/*   Updated: 2024/04/25 19:16:42 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_expand_string.h"
#include "../command_list/t_cmd_list.h"
#include "../character_list/char_list.h"
#include "../environment_variables/env.h"
#include "../character_checks/character_checks.h"
#include "../free/free.h"
#include "libft.h"
#include <stdlib.h>
#include <stddef.h>

extern void	_expand_string(char **arg_ptr, t_env *env);
static void	_add_literal_str(t_char_list **char_list, const char *arg,
				size_t *i);
static void	_add_env_expanded_str(t_char_list **char_list, const char *arg,
				size_t *i, t_env *env);
static void	_add_env_value(t_char_list **char_list, const char *arg,
				size_t *i, t_env *env);
static char	*_get_var_name(const char *str);

/**
 * 
 * @note
 * - A single '$' is seen as a literal character.
 * - '$' not followed by letter, digit, or underscore is not interpreted as
 *   environment variable.
 */
extern void	_expand_string(char **arg_ptr, t_env *env)
{
	size_t		i;
	t_char_list	*char_list;

	char_list = NULL;
	i = 0;
	while ((*arg_ptr)[i])
	{
		if ((*arg_ptr)[i] == '\'')
			_add_literal_str(&char_list, (*arg_ptr), &i);
		else if ((*arg_ptr)[i] == '\"')
			_add_env_expanded_str(&char_list, (*arg_ptr), &i, env);
		else if ((*arg_ptr)[i] == '$' && ((*arg_ptr)[i + 1] == '?'
			|| is_variable_name_start((*arg_ptr)[i + 1])))
		{
			_add_env_value(&char_list, *arg_ptr, &i, env);
			if ((*arg_ptr)[i] == '\0')
				return (_replace_arg(&char_list, arg_ptr, TO_NULL));
		}
		else
			char_list_add_char(&char_list, (*arg_ptr)[i++]);
	}
	_replace_arg(&char_list, arg_ptr, TO_EMPTY_STRING);
}

static void	_add_literal_str(t_char_list **char_list, const char *arg,
				size_t *i)
{
	(*i)++;
	while (arg[*i] && arg[*i] != '\'')
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
	while (arg[*i] && arg[*i] != '\"')
	{
		if (arg[*i] == '$'
			&& (is_variable_name_start(arg[*i + 1]) || arg[*i + 1] == '?'))
		{
			name = _get_var_name(&arg[*i]);
			(*i) += ft_strlen(name) + 1;
			value = env_get_value_by_name(env, name);
			char_list_add_str(char_list, value);
			free_and_null((void **)&name);
			free_and_null((void **)&value);
		}
		else
		{
			char_list_add_char(char_list, arg[*i]);
			(*i)++;
		}
	}
	if (arg[*i])
		(*i)++;
}

static void	_add_env_value(t_char_list **char_list, const char *arg,
				size_t *i, t_env *env)
{
	char	*name;
	char	*value;

	name = _get_var_name(&arg[*i]);
	value = env_get_value_by_name(env, name);
	if (ft_strlen(value) == 0)
	{
		free_and_null((void **)&value);
		value = NULL;
	}
	else
		char_list_add_str(char_list, value);
	free_and_null((void **)&name);
	free_and_null((void **)&value);
	if (ft_strncmp(&arg[*i], "$?", 2) == 0)
	{
		(*i) += 2;
		return ;
	}
	(*i)++;
	while (arg[*i] && is_variable_name_middle(arg[*i]))
		(*i)++;
}

/**
 * @note
 * - "$?" forms exit status regardless of the following charater;
 */
static char	*_get_var_name(const char *str)
{
	size_t	start;
	size_t	end;

	if (ft_strncmp(str, "$?", 2) == 0)
		return (ft_strdup("?"));
	start = 0;
	if (str[start] == '$')
		start++;
	end = start;
	if (str[end] && is_variable_name_start(str[end]))
		end++;
	while (str[end] && is_variable_name_middle(str[end]))
		end++;
	return (ft_strndup(&str[start], end - start));
}
