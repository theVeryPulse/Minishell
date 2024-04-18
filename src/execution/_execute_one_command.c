/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _execute_one_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:35:39 by Philip            #+#    #+#             */
/*   Updated: 2024/04/18 14:32:20 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../command_list/cmd_list.h"
#include "../environment_variables/env.h"
#include "../minishell/minishell.h"
#include "../signal_handler/signal_handler.h"
#include "../built_in/built_in.h"
#include <signal.h> /* signal */
#include <unistd.h> /* dup, dup2 */
#include <sys/types.h> /* pid_t */


