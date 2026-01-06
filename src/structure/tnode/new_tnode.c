/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tnode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:32:28 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/06 00:30:41 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tnode	*new_tnode(void *origin, void *data)
{
	t_tnode	*tnode;

	tnode = malloc(sizeof(t_tnode));
	if (!tnode)
		return (NULL);
	tnode->mstype = TNODE_T;
	tnode->data = data;
	tnode->type = WORD;
	tnode->origin = origin;
	tnode->branch = NULL;
	tnode->left = NULL;
	tnode->right = NULL;
	tnode->destroy = free;
	tnode->print = print_string;
	return (tnode);
}
