/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_astree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:10:57 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/06 00:29:28 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_astree	*new_astree(void *data)
{
	t_astree	*tree;

	tree = malloc(sizeof(t_astree));
	if (!tree)
		return (NULL);
	tree->mstype = ASTREE_T;
	tree->root = new_tnode(tree, data);
	tree->entry = tree->root;
	return (tree);
}
