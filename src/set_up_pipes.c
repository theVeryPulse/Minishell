/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:31:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/10 23:46:02 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include
#include "command_list/cmd_list.h"
#include "libft.h"
#include <unistd.h>

/**
 * @brief Set the up pipes object
 * 
 * @param cmds 
 * @return int* 
 * @note 
 * 
 * cmd_count 3
 * pipes = [0] [1] [2] [3] [4] [5]
 */
int	*set_up_pipes(t_cmd_list *cmds)
{
	int	cmd_count;
	t_cmd_list	*cmd;
	int	*pipes;
	int	i;

	cmd_count = 0;
	cmd = cmds;
	while (cmd)
	{
		cmd = cmd->next;
		cmd_count++;
	}
	pipes = (int *)ft_calloc((cmd_count - 1) * 2, sizeof(int));
	i = 0;
	while (i < (cmd_count - 1) * 2)
	{
		pipe(&pipes[i]);
		i += 2;
	}
	return (pipes);
}
/**
 * @brief 
 * 
 * @note
 * cd with only a relative or absolute path  same process
 * export with no options                    same process
 * unset with no options                     same process
 * exit with no options                      same process
 * pwd with no options                       child process
 * env with no options or arguments          child process
 */
bool	command_for_parent_process(const char *cmd)
{
	return (ft_strncmp(cmd, "cd", 3) == 0
			|| ft_strncmp(cmd, "exit", 5) == 0
			|| ft_strncmp(cmd, "unset", 6) == 0
			|| ft_strncmp(cmd, "export", 7) == 0);
}

#include "environment_variables/env.h"
#include "is_builtin_function.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
void	execute_cmds(t_cmd_list *cmds, t_env *env)
{
	int			*pipes;
	t_cmd_list	*cmd;
	int			pipe_idx;
	pid_t		id;

	printf("Execution\n");
	pipes = set_up_pipes(cmds);
	pipe_idx = 0;
	cmd = cmds;
	while (cmd)
	{
		if (cmd->cmd_argv)
			printf("  executing %s\n", cmd->cmd_argv[0]);
		if (!cmd->should_execute)
		{
			cmd = cmd->next;
			continue ;
		}
		if (cmd->cmd_argv && command_for_parent_process(cmd->cmd_argv[0]))
		{
			/* built-in functions that do not need redirect or pipe */
		}
		else
		{
			id = fork();
			if (id == 0)
				execve(cmd->cmd_argv[0], cmd->cmd_argv, env_build_envp(env));
		}
		close(pipes[pipe_idx]);
		close(pipes[pipe_idx + 1]);
		pipe_idx += 2;
		cmd = cmd->next;
	}
	waitpid(id, NULL, 0);
}





