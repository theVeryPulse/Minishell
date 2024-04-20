/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _execution.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 23:59:54 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 17:04:28 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../command_list/t_cmd_list.h"
#include "../environment_variables/t_env.h"
#include "../pipes/t_pipes.h"
#include "t_fd_action.h"
#include <sys/types.h> /* pid_t */

extern void	_execute_shell_script(const char *filepath, t_env **env);
extern void	_execute_one_command(t_cmd_list *cmd, t_env **env);
extern void	_execute_piped_commands(t_cmd_list *cmds, t_env **env);
extern int	_exit_status(pid_t id);
extern void	_apply_redirects(t_cmd_list *cmd);
extern int	_execute_builtin_function(char **argv, t_env **env,
				t_cmd_list *cmds, t_pipes *pipes);
extern void	_child_execute_target_command(t_cmd_list *cmd, t_env *env,
				t_pipes *pipes);
extern int	_stdin_stdout(t_fd_action action);
extern void	execute_line(char *line);
