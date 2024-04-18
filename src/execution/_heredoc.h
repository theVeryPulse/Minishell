/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _heredoc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:47:09 by Philip            #+#    #+#             */
/*   Updated: 2024/04/17 18:48:58 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HEREDOC_H
# define _HEREDOC_H

# define HEREDOC_FILE "./.heredoc_temp"

extern void	_heredoc(char *delimiter, int stdin_copy);

#endif