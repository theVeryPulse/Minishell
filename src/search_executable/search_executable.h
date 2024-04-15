/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_executable.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:56:13 by Philip            #+#    #+#             */
/*   Updated: 2024/04/15 13:01:13 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../command_list/cmd_list.h"
#include "../environment_variables/env.h"

void	search_executable(t_cmd_list *cmds, t_env *env);
void	search_exec_and_replace_arg(char **arg, char **paths);
