/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:09:47 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/06 00:42:59 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_astree	*parser(t_dlist *tokens)
{
	t_astree	*tree;

	tree = new_astree(NULL);
	tree->root = parse_expression(tree, &tokens->head);
	tree->entry = get_entry_astree(tree);
	return (tree);
}
