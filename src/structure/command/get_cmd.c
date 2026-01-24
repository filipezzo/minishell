/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:15:44 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/05 15:17:39 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_cmd(void *ptr)
{
	t_tnode	*node;
	t_cmd	*cmd;

	if (!ptr)
		return (NULL);
	node = (t_tnode *)ptr;
	if (node->mstype != TNODE_T && !node->data)
		return (NULL);
	cmd = (t_cmd *)node->data;
	if (cmd->mstype != COMMAND_T)
		return (NULL);
	return (cmd);
}
