/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:39:37 by Philip            #+#    #+#             */
/*   Updated: 2024/04/06 19:34:25 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"
#include "libft.h"
#include <unistd.h>

void	free_env_stack(t_env_stack **stack)
{
	t_env_stack	*node;
	t_env_stack	*next_node;

	if (!stack || !(*stack))
		return ;
	node = *stack;
	while (node)
	{
		next_node = node->next;
		free(node->name_value);
		free(node);
		node = next_node;
	}
	*stack = NULL;
}

char	*find_env_value_by_name(t_env_stack *stack, const char *name)
{
	t_env_stack	*node;
	size_t		i;

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

void	build_env_stack(t_env_stack	**stack)
{
	char			**env_var;

	*stack = NULL;
	env_var = __environ;
	while (env_var && *env_var)
	{
		add_to_env(stack, ft_strdup(*env_var));
		env_var++;
	}
}

void	add_to_env(t_env_stack **stack, char *name_value)
{
	t_env_stack	*new_node;

	new_node = (t_env_stack *)ft_calloc(1, sizeof(t_env_stack));
	new_node->next = NULL;
	if (*stack)
		new_node->next = *stack;
	*stack = new_node;
	new_node->name_value = ft_strdup(name_value);
}

void	remove_from_env_by_name(t_env_stack **stack, const char *name)
{
	t_env_stack	*node;
	t_env_stack	*prev;
	size_t		i;

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
