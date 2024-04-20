/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_append.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:29:41 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 15:06:33 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ENV_APPEND_H
# define _ENV_APPEND_H

# include "t_env.h" 

extern void	_env_append(t_env **list, const char *name_value);

#endif