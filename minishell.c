/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:49:09 by Philip            #+#    #+#             */
/*   Updated: 2024/04/01 18:08:14 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// readline
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <stdbool.h>
#include <stdlib.h>

// getcwd
#include <unistd.h>

// stat
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// signal
#include <signal.h>

// Check this command
// <output1 <output2 <outputnotexist <output4 cat >b > c  > d

void	prompt_on_new_line()
{
	// rl_redisplay();
	// rl_on_new_line();
	printf("\nminishell $ ");
}
// $env_var ' " < > << >> |

int	main(int argc, char const *argv[])
{
	char	buffer[100];

	if (!isatty(STDIN_FILENO))
		return (0);
	signal(SIGINT, prompt_on_new_line);
	getcwd(buffer, 100);
	printf("%s\n", buffer);
	printf("%s\n", *__environ);
	printf("ttyname: %s\n", ttyname(STDIN_FILENO));
	printf("STDIN isatty = %d\n", isatty(STDIN_FILENO));
	printf("STDOUT isatty = %d\n", isatty(STDOUT_FILENO));
	printf("STDERR isatty = %d\n", isatty(STDERR_FILENO));

	add_history("Second to latest command");
	add_history("Latest command");

	while (true)
	{
		free(readline("minishell $ "));
		printf("((%s))\n", rl_line_buffer);
	}
	return 0;
}
