/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables_part2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:39:37 by Philip            #+#    #+#             */
/*   Updated: 2024/04/06 23:36:50 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"
#include "libft.h"
#include <unistd.h>

char	**build_envp(t_env_stack *stack)
{
	int			i;
	int			len;
	char		**envp;
	t_env_stack	*node;

	node = stack;
	len = 0;
	while (node)
	{
		node = node->next;
		len++;
	}
	envp = (char **)ft_calloc(len + 1, sizeof(char *));
	i = len - 1;
	node = stack;
	while (node)
	{
		envp[i--] = ft_strdup(node->name_value);
		node = node->next;
	}
	return (envp);
}

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
