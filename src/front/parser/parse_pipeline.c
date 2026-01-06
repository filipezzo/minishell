/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:35:13 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/05 18:39:53 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tnode	*parse_pipeline(t_astree *tree, t_bnode **cursor)
{
	t_tnode		*node;
	t_tnode		*aux;
	t_lextoken	*token;

	aux = parse_command(tree, cursor);
	if (!aux)
		return (NULL);
	token = get_lextoken(*cursor);
	while (token && token->type == PIPE)
	{
		node = new_tnode(tree, ft_strdup(token->content));
		node->type = token->type;
		node->left = aux;
		node->left->branch = node;
		next_lextoken(cursor);
		node->right = parse_command(tree, cursor);
		if (!node->right)
			return (NULL);
		node->right->branch = node;
		aux = node;
		token = get_lextoken(*cursor);
	}
	return (aux);
}
