/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables_part2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:39:37 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 17:01:42 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

char	**env_build_envp(t_env *stack)
{
	int		i;
	int		len;
	char	**envp;
	t_env	*node;

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

void	env_free(t_env **stack)
{
	t_env	*node;
	t_env	*next_node;

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
