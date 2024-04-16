/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _expand_string.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:55:44 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 01:08:53 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _EXPAND_STRING_H
# define _EXPAND_STRING_H

# include "../environment_variables/t_env.h"

void	_expand_string(char **arg_ptr, t_env *env);

#endif
