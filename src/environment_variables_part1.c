/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables_part1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:39:37 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 17:01:33 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static void	add_to_env(t_env **stack, const char *name_value);

char	*env_get_value_by_name(t_env *stack, const char *name)
{
	t_env	*node;
	size_t	i;

	node = stack;
	while (node)
	{
		i = 0;
		while (node->name_value[i] == name[i])
			i++;
		if (node->name_value[i] == '=' && name[i] == '\0')
			return (ft_strdup(&(node->name_value[i + 1])));
		node = node->next;
	}
	return (NULL);
}

void	env_build(t_env **stack)
{
	char	**env_var;

	*stack = NULL;
	env_var = __environ;
	while (env_var && *env_var)
	{
		add_to_env(stack, *env_var);
		env_var++;
	}
	add_to_env(stack, "?=0");
}

/*
3 cases of removing a node:

start: (node == *stack)
A->B->C
B->C->NULL

middle: prev->next = node->next;
A->B->C->NULL
A->C->NULL

end: prev->next = node->next;
A->B->C->NULL
A->B->NULL

 */

void	env_remove_by_name(t_env **stack, const char *name)
{
	t_env	*node;
	t_env	*prev;
	size_t	i;

	node = *stack;
	while (node)
	{
		i = 0;
		while (node->name_value[i] == name[i])
			i++;
		if (node->name_value[i] == '=' && name[i] == '\0')
		{
			if (node == *stack)
				*stack = node->next;
			else
				prev->next = node->next;
			return (free(node->name_value), free(node));
		}
		prev = node;
		node = node->next;
	}
}

void	env_update_name_value(t_env **stack, const char *name_value)
{
	t_env	*node;
	size_t	i;

	node = *stack;
	while (node)
	{
		i = 0;
		while (node->name_value[i] == name_value[i])
			i++;
		if (i > 0 && node->name_value[i - 1] == '=' && name_value[i - 1] == '=')
		{
			free(node->name_value);
			node->name_value = ft_strdup(name_value);
			return ;
		}
		node = node->next;
	}
	add_to_env(stack, name_value);
}

static void	add_to_env(t_env **stack, const char *name_value)
{
	t_env	*new_node;

	new_node = (t_env *)ft_calloc(1, sizeof(t_env));
	new_node->next = NULL;
	if (*stack)
		new_node->next = *stack;
	*stack = new_node;
	new_node->name_value = ft_strdup(name_value);
}
