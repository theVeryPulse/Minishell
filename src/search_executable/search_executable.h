/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_executable.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:56:13 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 01:23:55 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCH_EXECUTABLE_H
# define SEARCH_EXECUTABLE_H

# include "../command_list/t_cmd_list.h" // [x] t_cmd_list.h
# include "../environment_variables/t_env.h" // [x] t_env.h

void	search_exec_and_replace_arg_in_cmds(t_cmd_list *cmds, t_env *env);
void	search_exec_and_replace_arg(char **arg, t_env *env);

#endif