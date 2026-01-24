/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_tnode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:44:07 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/22 22:38:34 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_tnode(void *ptr)
{
	t_tnode	*node;
	void	*data;

	if (!ptr)
		return ;
	node = (t_tnode *)ptr;
	if (node->mstype != TNODE_T)
		return ;
	data = node->data;
	if (node->destroy)
		node->destroy(data);
	else
		free(node->data);
	node->destroy = NULL;
	node->print = NULL;
	free(node);
}
