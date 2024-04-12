/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuleung <chuleung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 21:15:26 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/12 21:40:08 by chuleung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environment_variables/env.h"
#include "../environment_variables/_env.h"
#include <stdlib.h>
#include <unistd.h>

void builtin_export(t_env *env, char *cmd_argv)
{
    if (ft_unset(cmd_argv[0], "unset", 6))
        exit (1);
    env_remove_by_name(&env, cmd_argv[1]);
}
