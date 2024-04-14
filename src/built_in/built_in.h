/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:32:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/15 00:20:34 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../environment_variables/env.h"

int	builtin_pwd(void);
int	builtin_export(t_env **env, char **cmd_argv);
int	builtin_cd(t_env **env, char **cmd_argv);
int	builtin_echo(char **argv);
int builtin_env(t_env *env, char **argv);

#endif
