/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _t_to_free.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:34:49 by Philip            #+#    #+#             */
/*   Updated: 2024/04/15 20:38:07 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _T_TO_FREE_H
# define _T_TO_FREE_H

# include "../command_list/cmd_list.h"
# include "../environment_variables/env.h"
# include "../pipes/t_pipes.h"

typedef struct	s_to_free
{
	t_cmd_list	*cmds;
	t_env		*env;
	t_pipes		*pipes;
}	t_to_free;

#endif