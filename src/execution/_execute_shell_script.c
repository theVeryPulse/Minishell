/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _execute_shell_script.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:06:18 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 17:13:33 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_execution.h"
#include "../minishell/minishell.h" /* minishell */
#include "../signal_handler/signal_handler.h" /* sigint_sigquit_handler */
#include "../exit_status.h" /* _exit_status */
#include "../environment_variables/env.h" /* env_update_exit_status */
#include "libft.h" /* ft_dprintf */
#include <sys/stat.h> /* stat */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* STDERR_FILENO, fork */
#include <fcntl.h> /* open */
#include <readline/readline.h> /* rl_clear_history */
#include <stdio.h> /* perror */
#include <stdlib.h> /* exit, free */

extern void	_execute_shell_script(const char *filepath, t_env **env);
static void	_execute_script_child(const char *filepath);
static void	_read_line_from_file_and_execute(int file);
static bool	contains_only_spaces(char *line);

/**
 * @brief Checks shell script file status, then fork a child process to read and
 *        execute the file line by line.
 * 
 * @param filepath Shell scrip file path.
 * @param env Pointer to the pointer to the environment variables.
 */
extern void	_execute_shell_script(const char *filepath, t_env **env)
{
	struct stat	statbuf;
	pid_t		id;

	if (stat(filepath, &statbuf) != 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: No such file or directory\n",
			filepath);
		return (env_update_exit_status(env, NO_SUCH_FILE_EXIT_STATUS));
	}
	else if (S_ISDIR(statbuf.st_mode))
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: Is a director\n", filepath);
		return (env_update_exit_status(env, IS_A_DIRECTORY_EXIT_STATUS));
	}
	else if (!(statbuf.st_mode & S_IXUSR) || !(statbuf.st_mode & S_IRUSR))
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: permission denied\n",
			filepath);
		return (env_update_exit_status(env, PERMISSION_DENIED_EXIT_STATUS));
	}
	id = fork();
	if (id == 0)
		_execute_script_child(filepath);
	env_update_exit_status(env, _exit_status(id));
}

static void	_execute_script_child(const char *filepath)
{
	int	file;

	ft_dprintf(STDERR_FILENO, "executing %s\n", filepath);
	rl_clear_history();
	file = open(filepath, O_RDONLY);
	if (file == -1)
	{
		perror(filepath);
		exit(1);
	}
	minishell_free();
	minishell_init();
	while (true)
		_read_line_from_file_and_execute(file);
}

static void	_read_line_from_file_and_execute(int file)
{
	char	*line_without_nl;
	char	*line;

	sigint_sigquit_handler(DEFAULT);
	line = get_next_line(file);
	if (line == NULL)
	{
		env_free(&(minishell()->env));
		exit (minishell()->exit_status);
	}
	if (contains_only_spaces(line))
	{
		free(line);
		return ;
	}
	line_without_nl = ft_strtrim(line, "\n");
	ft_dprintf(STDERR_FILENO, "$ %s\n", line_without_nl);
	execute_line(line_without_nl);
	free(line_without_nl);
	free(line);
}

static bool	contains_only_spaces(char *line)
{
	while (ft_isspace(*line))
		line++;
	return (*line == '\0');
}
