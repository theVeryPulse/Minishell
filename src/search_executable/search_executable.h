/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_executable.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:56:13 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 19:10:59 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCH_EXECUTABLE_H
# define SEARCH_EXECUTABLE_H

# include "../command_list/t_cmd_list.h"
# include "../environment_variables/t_env.h"

extern void	search_executable_in_commands(t_cmd_list *cmds, t_env *env);
extern void	search_executable(char **arg, t_env *env);

#endif