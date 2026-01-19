/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:05:07 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/19 01:45:03 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_cmd(void *ptr)
{
	t_cmd	*cmd;

	if (!ptr)
		return ;
	cmd = (t_cmd *)ptr;
	if (cmd->mstype != COMMAND_T)
		return ;
	destroy_cmtx(cmd->args);
	destroy_lst_redir(cmd->redirections);
	free(cmd);
}
