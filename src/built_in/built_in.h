/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:32:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/15 20:16:32 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../environment_variables/env.h"
# include "../command_list/cmd_list.h"
# include "../pipes/t_pipes.h"
# include <stdbool.h>

bool	is_builtin_function(const char *cmd);
int		builtin_pwd(void);
int		builtin_cd(t_env **env, char **cmd_argv);
int		builtin_echo(char **argv);
int 	builtin_env(t_env *env, char **argv);
void	builtin_exit(char **cmd_argv, t_env **env, t_cmd_list *cmds,
			t_pipes *pipes);
int		builtin_export(t_env **env, char **cmd_argv);
int		builtin_unset(char **cmd_argv, t_env **env);

#endif
