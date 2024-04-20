/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:02:53 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 14:51:42 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ENV_H
# define T_ENV_H

typedef struct s_env	t_env;
typedef struct s_env
{
	/* A string in the format of "NAME=VALUE", e.g. USER=admin */
	char	*name_value;
	t_env	*next;
}	t_env;

#endif