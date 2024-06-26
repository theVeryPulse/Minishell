/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _expand_string.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:55:44 by Philip            #+#    #+#             */
/*   Updated: 2024/04/25 19:18:51 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _EXPAND_STRING_H
# define _EXPAND_STRING_H

# include "../environment_variables/t_env.h"
# include "../character_list/t_char_list.h"
# include <stdbool.h>

typedef enum e_mode
{
	TO_NULL,
	TO_EMPTY_STRING
}	t_mode;

extern void	_expand_string(char **arg_ptr, t_env *env);
extern bool	_is_variable_name(char *arg);
extern void	_replace_arg(t_char_list **char_list, char **arg_ptr,
				t_mode mode);
#endif
