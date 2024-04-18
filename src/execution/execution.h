/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:32:31 by Philip            #+#    #+#             */
/*   Updated: 2024/04/17 23:42:42 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../command_list/t_cmd_list.h"
# include "../environment_variables/t_env.h"
# include "../pipes/t_pipes.h"
# include <sys/types.h>

extern void	execute_script_child(const char *filepath);
extern void	_child_execute_target_command(t_cmd_list *cmd, t_env *env,
				t_pipes *pipes);
void	_execute_one_command(t_cmd_list *cmd, t_env **env);
void	_apply_redirects(t_cmd_list *cmd, int stdin_copy);
int	get_last_child_exit_status(pid_t id);
int	_execute_shell_script(const char *filepath);

#endif 