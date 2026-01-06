/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_astree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:57:03 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/05 19:52:21 by mhidani          ###   ########.fr       */
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
	if (!cursor)
		return ;
	destroy_ast_branch(cursor->left);
	destroy_ast_branch(cursor->right);
	destroy_tnode(cursor);
}
