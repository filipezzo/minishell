/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:01:48 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/05 18:36:55 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tnode	*parse_and_or(t_astree *tree, t_bnode **cursor)
{
	t_tnode		*node;
	t_tnode		*aux;
	t_lextoken	*token;

	aux = parse_pipeline(tree, cursor);
	if (!aux)
		return (NULL);
	token = get_lextoken(*cursor);
	while (token && (token->type == OR || token->type == AND))
	{
		node = new_tnode(tree, ft_strdup(token->content));
		node->type = token->type;
		node->left = aux;
		node->left->branch = node;
		next_lextoken(cursor);
		node->right = parse_pipeline(tree, cursor);
		if (!node->right)
			return (destroy_tnode(node), NULL);
		node->right->branch = node;
		aux = node;
		token = get_lextoken(*cursor);
	}
	return (aux);
}
