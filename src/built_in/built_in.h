/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:32:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/14 12:54:23 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

int	builtin_pwd(void);
int	builtin_export(t_env **env, char **cmd_argv);
int	builtin_cd(t_env **env, char **cmd_argv);
int	builtin_echo(char **argv);

#endif
