/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:49:09 by Philip            #+#    #+#             */
/*   Updated: 2024/04/02 03:19:11 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

typedef struct s_cmd_list t_cmd_list;

struct s_cmd_list
{
	char		**cmd_argv; // {"echo", "-n", "123", NULL}
	char		**redirect; // {"<infile", "<<delimiter", ">outfile", ">>outfile"}
	t_cmd_list	*next;
};

t_cmd_list	*cmd_list_last(t_cmd_list *list)
{
	while (list->next)
	{
		list = list->next;
	}
	return (list);
}

void	cmd_list_append(t_cmd_list **list, t_cmd_list *node)
{
	if (!list)
		return;
	if (!(*list))
		*list = node;
	else
		cmd_list_last(*list)->next = node;
}

t_cmd_list	*cmd_list_new(void)
{
	return((t_cmd_list *)ft_calloc(1, sizeof(t_cmd_list)));
}

bool	is_divider(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

// Lexical analysis, sometimes referred to as tokenizer
// Translates line into tokens. 
// $env_var ' " < > << >> |
// echo -n 123 321
// echo -n 123 321 | cat
t_cmd_list	*analyze_leximes(const char *line)
{
	size_t		i;
	size_t		analysis_idx;
	t_cmd_list	*cmds;
	t_cmd_list	*this_cmd;
	t_list		*this_cmd_argv_list;
	t_list		*this_cmd_redirect_list;

	this_cmd_argv_list = NULL;
	this_cmd_redirect_list = NULL;
	cmds = NULL;
	this_cmd = cmd_list_new();
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		if (line[i] == '|')         /* Pipe */
		{
			// printf("Detects pipe |\n");
			cmd_list_append(&cmds, this_cmd);
			i++;
			while (line[i] && ft_isspace(line[i]))
				i++;
			this_cmd = cmd_list_new();
		}
		else if (line[i] == '<')
			if (line[i + 1] == '<') /* Heredoc */
				;
			else                    /* Infile redirect */
				;
		else if (line[i] == '>')
			if (line[i + 1] == '>') /* Outfile append */
				;
			else                    /* Outfile truncate */
				;
		else if (line[i] == '\'')   /* ' single quotes */
			;
		else if (line[i] == '\"')   /* " Double quotes */
			;
		else if (line[i] == '$')    /* Variable */
			;
		else                        /* The command "echo" */
		{
			/* Extract command */
			analysis_idx = i;
			while (line[i] && line[i] != '|')
			{
				/* Append redirect to linked list */
				if (is_divider(line[i]))
				{
					// printf("Detectes divider %c\n", line[i]);
					// TODO Left here
					// <<    END
					// <  infile
					// > outfile
					// >>outfile

					/* Finds out the redirect instruction string length */
					int	redirect_str_len;
					char	*redirect_str;

					redirect_str_len = 0;
					while (is_divider(line[analysis_idx]))
					{
						analysis_idx++;
						redirect_str_len++;
					}
					while (line[analysis_idx] && ft_isspace(line[analysis_idx]))
						analysis_idx++;
					while (line[analysis_idx]
						&& !ft_isspace(line[analysis_idx])
						&& !is_divider(line[analysis_idx]))
					{
						analysis_idx++;
						redirect_str_len++;
					}
					redirect_str = (char *)ft_calloc(redirect_str_len + 1, sizeof(char));

					/* Duplicates the redirect instruction string */
					int	redirect_str_idx;

					redirect_str_idx = 0;
					analysis_idx = i;
					while (is_divider(line[analysis_idx]))
					{
						redirect_str[redirect_str_idx++] = line[analysis_idx++];
					}
					while (line[analysis_idx] && ft_isspace(line[analysis_idx]))
						analysis_idx++;
					while (line[analysis_idx]
						&& !ft_isspace(line[analysis_idx])
						&& !is_divider(line[analysis_idx]))
					{
						redirect_str[redirect_str_idx++] = line[analysis_idx++];
					}
					ft_lstadd_back(&this_cmd_redirect_list,
									ft_lstnew((void *)redirect_str));
					printf("%s\n", (char *)ft_lstlast(this_cmd_redirect_list)->content);
					i = analysis_idx;

					// TODO Convert list to string array and assign to command
				}



				/* Append command name/argument to linked list */
				while (line[analysis_idx]
				&& !ft_isspace(line[analysis_idx])
				&& !is_divider(line[analysis_idx])) // "'$USER'" "\"$USER\""
					analysis_idx++;
				ft_lstadd_back(&this_cmd_argv_list,
						ft_lstnew((void *)ft_strndup(&line[i], analysis_idx - i)));
				printf("%s\n", (char *)ft_lstlast(this_cmd_argv_list)->content);

				/* Skip spaces until next argument or \0 is found */
				while (line[analysis_idx] && ft_isspace(line[analysis_idx]))
					analysis_idx++;
				i = analysis_idx;
			}

			/* Converts linked list to argv string array */
			int		cmd_argc;
			int		argv_idx;
			t_list	*node;

			cmd_argc = ft_lstsize(this_cmd_argv_list);
			this_cmd->cmd_argv = (char **)ft_calloc(cmd_argc + 1, sizeof(char *));
			argv_idx = 0;
			while (cmd_argc)
			{
				node = this_cmd_argv_list;
				this_cmd->cmd_argv[argv_idx] = (char *)this_cmd_argv_list->content;
				this_cmd_argv_list = this_cmd_argv_list->next;
				free(node);
				argv_idx++;
				cmd_argc--;
			}
			
		}
	}
	cmd_list_append(&cmds, this_cmd);
	
	// return (cmds);

	t_cmd_list	*cmd;
	t_cmd_list	*next_cmd;
	int			argv_idx;

	cmd = cmds;
	while (cmd)
	{
		next_cmd = cmd->next;
		printf("===Command===\n");
		argv_idx = 0;
		while (cmd->cmd_argv[argv_idx])
		{
			printf("%s\n", cmd->cmd_argv[argv_idx]);
			free(cmd->cmd_argv[argv_idx]);
			argv_idx++;
		}
		free(cmd->cmd_argv);
		free(cmd);
		cmd = next_cmd;
	}
}


int	main(void)
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

	char	*line;

	while (true)
	{
		line = readline("minishell $ ");
		printf("((%s))\n", rl_line_buffer);
		analyze_leximes(line);
		free(line);
	}
	return 0;
}
