/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:07:24 by Philip            #+#    #+#             */
/*   Updated: 2024/04/19 00:49:54 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_expand_string.h"
#include "../command_list/t_cmd_list.h"
#include "../character_list/char_list.h"
#include "../environment_variables/t_env.h"
#include "../free/free.h"
#include "libft.h"
#include <stddef.h>

static void	_shift_all_following_args_left(char **argv, int i);

void	_add_to_char_list_until(t_char_list **char_list, char end, char *arg,
			size_t *i)
{
	(*i)++;
	while (arg[*i] && arg[*i] != end)
		char_list_add_char(char_list, arg[(*i)++]);
	(*i)++;
}

void	_expand_delimeter(char **arg_ptr)
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
		if (arg[i] == '\'' || arg[i] == '\"')
			_add_to_char_list_until(&char_list, arg[i], arg, &i);
		else
			char_list_add_char(&char_list, arg[i++]);
	}
	expanded = char_list_to_str(char_list);
	free_and_null((void **)arg_ptr);
	*arg_ptr = expanded;
	char_list_free_and_null(&char_list);
}

/**
 * @brief Expands environment variables in command arguments and redirects.
 *
 * @param cmds A pointer to the head of the linked list of command nodes.
 * @param env  A pointer to the head of the linked list of environment
 *             variables.
 */
void	expand_arguments(t_cmd_list *cmd, t_env *env)
{
	int	i;

	while (cmd)
	{
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			_expand_string(&(cmd->argv[i]), env);
			if (cmd->argv[i] == NULL)
				_shift_all_following_args_left(cmd->argv, i);
			i++;
		}
		i = 0;
		while (cmd->redirects && cmd->redirects[i])
		{
			if (ft_strncmp("<<", cmd->redirects[i], 2) == 0)
				_expand_delimeter(&(cmd->redirects[i]));
			else
				_expand_string(&(cmd->redirects[i]), env);
			i++;
		}
		cmd = cmd->next;
	}
}

static void	_shift_all_following_args_left(char **argv, int i)
{
	argv[i] = argv[i + 1];
	while (argv[i])
	{
		argv[i] = argv[i + 1];
		i++;
	}
}
