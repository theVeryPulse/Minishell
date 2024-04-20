/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:23:53 by Philip            #+#    #+#             */
/*   Updated: 2024/04/20 14:42:34 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LIST_H
# define CMD_LIST_H

# include "t_cmd_list.h"

extern t_cmd_list	*cmd_list_new(void);
extern t_cmd_list	*cmd_list_last(t_cmd_list *list);
extern void			cmd_list_append(t_cmd_list **list, t_cmd_list *node);
extern void			cmd_list_free(t_cmd_list **list);
extern int			cmd_list_len(t_cmd_list *list);

#endif