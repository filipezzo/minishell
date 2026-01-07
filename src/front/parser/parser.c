/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:09:47 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/07 17:25:53 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_astree	*parser(t_dlist *tokens)
{
	t_astree	*tree;
	t_bnode		*cursor;

	cursor = tokens->head;
	tree = new_astree();
	tree->root = parse_and_or(tree, &cursor);
	tree->entry = get_entry_astree(tree);
	return (tree);
}
