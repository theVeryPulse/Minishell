/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:32:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 01:09:22 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../environment_variables/t_env.h"
# include "../command_list/cmd_list.h"
# include "../pipes/t_pipes.h"
# include <stdbool.h>

bool	is_builtin_function(const char *cmd);
int		builtin_pwd(void);
int		builtin_cd(char **cmd_argv, t_env **env);
int		builtin_echo(char **argv);
int 	builtin_env(char **argv, t_env *env);
void	builtin_exit(char **cmd_argv, t_env *env, t_cmd_list *cmds,
			t_pipes *pipes);
int		builtin_export(char **cmd_argv, t_env **env);
int		builtin_unset(char **cmd_argv, t_env **env);

#endif
