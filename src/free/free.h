/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:22:01 by Philip            #+#    #+#             */
/*   Updated: 2024/04/16 16:09:12 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "t_to_free.h"

extern void	free_and_null(void **ptr);
extern void	free_string_array_and_null(char ***string_array);
extern void	free_cmds_env_pipes_rl_clear_history(t_to_free to_free);

#endif
