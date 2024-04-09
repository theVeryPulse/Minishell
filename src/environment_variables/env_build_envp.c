/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:28:51 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 02:44:11 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

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
