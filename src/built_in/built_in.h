/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:32:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 16:33:23 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../environment_variables/t_env.h"
# include "../command_list/t_cmd_list.h"
# include "../pipes/t_pipes.h"
# include "libft.h"
# include <stdbool.h>

extern bool	is_builtin_function(const char *cmd);
extern int	exec_builtin_function(char **argv, t_env **env, t_cmd_list *cmds,
				t_pipes *pipes);

/* Individual built-in functions */

extern int	builtin_pwd(void);
extern int	builtin_cd(char **argv, t_env **env);
extern int	builtin_echo(char **argv);
extern int	builtin_env(char **argv, t_env *env, t_cmd_list *cmds,
				t_pipes *pipes);
extern void	builtin_exit(char **argv, t_env *env, t_cmd_list *cmds,
				t_pipes *pipes);
extern int	builtin_export(char **argv, t_env **env);
extern int	builtin_unset(char **argv, t_env **env);

#endif
