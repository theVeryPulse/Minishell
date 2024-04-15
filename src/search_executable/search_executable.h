/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_executable.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:56:13 by Philip            #+#    #+#             */
/*   Updated: 2024/04/15 13:47:42 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCH_EXECUTABLE_H
# define SEARCH_EXECUTABLE_H

# include "t_paths.h"
# include "../command_list/cmd_list.h" // [ ] t_cmd_list.h
# include "../environment_variables/env.h" // [ ] t_env.h

void	search_exec_and_replace_arg_in_cmds(t_cmd_list *cmds, t_env *env);
void	search_exec_and_replace_arg(char **arg, t_paths paths);

#endif