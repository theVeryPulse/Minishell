/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 00:48:17 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 02:11:58 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../command_list/t_cmd_list.h"
# include "../environment_variables/t_env.h"

extern void	execute_line(char *line);
extern void	execute_commands(t_cmd_list *cmds, t_env **env);

#endif