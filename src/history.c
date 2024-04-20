/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:39:15 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 20:15:49 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <readline/history.h>
#include <stdlib.h>

/**
 * @brief Reads command history from ".minishell_history" and adds it to the
 *        readline history.
 *
 * @return `int` The file descriptor of the opened history file, or -1 upon
 *         error.
 */
extern int	read_history_from_file(void)
{
	int		history;
	char	*line;
	char	*untrimmed;

	history = open(".minishell_history", O_RDWR | O_CREAT | O_APPEND, 0755);
	if (history == -1)
		return (-1);
	untrimmed = get_next_line(history);
	while (untrimmed)
	{
		line = ft_strtrim(untrimmed, "\n");
		add_history(line);
		free(line);
		free(untrimmed);
		untrimmed = get_next_line(history);
	}
	return (history);
}
