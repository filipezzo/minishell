/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:23:21 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/07 17:38:53 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tnode	*parse_subshell(t_astree *tree, t_bnode **cursor)
{
	t_tnode		*node;
	t_tnode		*aux;
	t_lextoken	*token;

	next_lextoken(cursor);
	aux = parse_and_or(tree, cursor);
	if (!aux)
		return (NULL);
	token = get_lextoken(*cursor);
	if (!token || token->type != RIGHT_PAREN)
		return (destroy_tnode(aux), NULL);
	node = new_tnode(tree, ft_strdup("SUBSHELL"));
	if (!node)
		return (destroy_tnode(aux), NULL);
	node->type = SUBSHELL;
	node->left = aux;
	node->left->branch = node;
	next_lextoken(cursor);
	return (node);
}
