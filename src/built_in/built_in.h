/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuleung <chuleung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:32:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/15 17:54:19 by chuleung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../environment_variables/env.h"
# include "../command_list/cmd_list.h"
# include "../pipes/pipes.h"

int	builtin_pwd(void);
int	builtin_cd(t_env **env, char **cmd_argv);
int	builtin_echo(char **argv);
int builtin_env(t_env *env, char **argv);
void	builtin_exit(char **cmd_argv, t_env **env, t_cmd_list *cmds,
			t_pipes *pipes);
int	builtin_export(t_env **env, char **cmd_argv);
int	builtin_unset(char **cmd_argv, t_env **env);

#endif
