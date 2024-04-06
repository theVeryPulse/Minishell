/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:39:15 by Philip            #+#    #+#             */
/*   Updated: 2024/04/06 16:22:28 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <readline/history.h>

/**
 * @brief Reads command history from a file and adds it to the readline history.
 *
 * @note This function attempts to open ".minishell_history" and read each line 
 * of it. Each line's newline character is trimmed before getting added to the 
 * readline history.
 *
 * @return The file descriptor of the opened history file, or -1 if an error occurs.
 */
int	read_history_from_file()
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
