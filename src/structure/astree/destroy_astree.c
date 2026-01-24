/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_astree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:57:03 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/23 17:37:34 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	destroy_ast_branch(t_tnode *cursor);

void	destroy_astree(void *ptr)
{
	t_astree	*tree;

	if (!ptr)
		return ;
	tree = (t_astree *)ptr;
	if (tree->mstype != ASTREE_T)
		return ;
	destroy_ast_branch(tree->root);
	free(tree);
}

static void	destroy_ast_branch(t_tnode *cursor)
{
	t_tnode	*left;
	t_tnode	*right;

	if (!cursor)
		return ;
	left = cursor->left;
	right = cursor->right;
	destroy_ast_branch(left);
	destroy_ast_branch(right);
	destroy_tnode(cursor);
}
