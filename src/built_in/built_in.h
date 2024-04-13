/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuleung <chuleung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:32:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/13 14:20:56 by chuleung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

int	builtin_pwd(void);
int	builtin_export(t_env **env, char **cmd_argv);
int builtin_cd(t_env **env, char **cmd_argv);

#endif
