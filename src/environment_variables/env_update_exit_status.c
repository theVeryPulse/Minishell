/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update_exit_status.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:42:11 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 16:44:36 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../free/free.h"
#include "libft.h"

/**
 * @brief Updates the exit status ($?) saved in environment.
 * 
 * @param env Pointer to the environment variables list.
 * @param exit_status Exit status to save into environment.
 */
extern void	env_update_exit_status(t_env **env, int exit_status)
{
	char	*exit_status_str;
	char	*exit_status_name_value;

	exit_status_str = ft_itoa(exit_status);
	exit_status_name_value = ft_format_string("?=%s", exit_status_str);
	env_update_name_value(env, exit_status_name_value);
	free_and_null((void **)&exit_status_str);
	free_and_null((void **)&exit_status_name_value);
}
