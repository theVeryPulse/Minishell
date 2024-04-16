/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:28:51 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 01:48:25 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_env.h"
#include "libft.h"

/**
 * @brief Builds an environment variables string array from a linked list of
 *        environment variables.
 *        The array of strings (envp) is suitable for passing to execve().
 *
 * @param list A pointer to the head of the linked list of environment 
 *             variables.
 * @return     A pointer to the array of strings (envp) terminated by NULL.
 *             This array should be freed by the caller when no longer needed.
 */
char	**env_build_envp(t_env *list)
{
	int		i;
	int		len;
	char	**envp;
	t_env	*node;

	node = list;
	len = 0;
	while (node)
	{
		node = node->next;
		len++;
	}
	envp = (char **)ft_calloc(len + 1, sizeof(char *));
	i = 0;
	node = list;
	while (node)
	{
		envp[i] = ft_strdup(node->name_value);
		node = node->next;
		i++;
	}
	return (envp);
}
