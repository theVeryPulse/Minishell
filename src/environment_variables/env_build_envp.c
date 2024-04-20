/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:28:51 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 15:16:00 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_env.h"
#include "libft.h" /* ft_calloc, ft_strdup */

/**
 * @brief Builds an environment variables string array from a linked list of
 *        environment variables.
 *        The array of strings (envp) is suitable for passing to execve().
 *
 * @param list Pointer environment variables.
 * @return     Array of strings (envp) terminated by NULL.
 *             This array must be freed by the caller after use.
 */
extern char	**env_build_envp(t_env *list)
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
