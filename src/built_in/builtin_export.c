/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuleung <chuleung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:43:07 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/12 21:34:24 by chuleung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environment_variables/env.h"
#include "../environment_variables/_env.h"
#include <stdlib.h>
#include <unistd.h>

void builtin_export(t_env *env, char *cmd_argv)
{
    if (ft_strncmp(cmd_argv[0], "export", 7))
        exit (1);
    env_update_name_value(&env, cmd_argv[1]);
}

/*
void export_var(char *name, char *value)
{
    int     id;
    char    *new_env[] = env_update_name_value(env, )
    char    *new_argv[] = {"/bin/bash", "-c", "echo $MY_VARIABLE", NULL};

    if (fork() == 0)
    {
        execve("/bin/echo", new_argv, new_env);
        exit(EXIT_FAILURE);
    } 
    else 
        wait(NULL);
}
*/
