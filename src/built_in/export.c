/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuleung <chuleung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:43:07 by chuleung          #+#    #+#             */
/*   Updated: 2024/04/11 21:45:42 by chuleung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_env.h"
#include <stdlib.h>
#include <unistd.h>

#include "../environment_variables/env.h"


void export(char **argv, t_env *env)
{
    int id;
    char *name_value;

    //sth that can argv into a array of arg strings
    env_update_name_value(&env, &(argv[1]));

    id = fork();
    if (id == 0)
    {
        e
        perror("EXIT_FAILURE")
    }
    else
        wait(NULL);
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
