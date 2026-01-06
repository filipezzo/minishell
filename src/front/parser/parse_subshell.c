/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:23:21 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/05 18:53:27 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tnode	*parse_subshell(t_astree *tree, t_bnode **cursor)
{
	t_tnode	*node;
	t_tnode	*aux;

	next_lextoken(cursor);
	aux = parse_expression(tree, cursor);
	if (!aux)
		return (NULL);
	node = new_tnode(tree, ft_strdup("subshell"));
	node->type = SUBSHELL;
	node->left = aux;
	node->left->branch = node;
	next_lextoken(cursor);
	return (node);
}
