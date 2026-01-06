/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expression.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:01:48 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/05 18:36:55 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_expression(t_type type);

t_tnode	*parse_expression(t_astree *tree, t_bnode **cursor)
{
	t_tnode		*node;
	t_tnode		*aux;
	t_lextoken	*token;

	aux = parse_pipeline(tree, cursor);
	if (!aux)
		return (NULL);
	token = get_lextoken(*cursor);
	while (token && is_expression(token->type))
	{
		node = new_tnode(tree, ft_strdup(token->content));
		node->type = token->type;
		node->left = aux;
		node->left->branch = node;
		next_lextoken(cursor);
		node->right = parse_pipeline(tree, cursor);
		if (!node->right)
			return (NULL);
		node->right->branch = node;
		aux = node;
		token = get_lextoken(*cursor);
	}
	return (aux);
}

static t_bool	is_expression(t_type type)
{
	return (
		type == OR
		|| type == AND
		|| type == SEPARATOR
		|| type == BACKGROUND
	);
}
