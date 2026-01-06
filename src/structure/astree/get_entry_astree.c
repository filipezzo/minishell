/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_entry_astree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:49:38 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/05 19:20:35 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tnode	*find_entry_astree(t_tnode *cursor);

t_tnode	*get_entry_astree(t_astree *tree)
{
	return (find_entry_astree(tree->root));
}

static t_tnode	*find_entry_astree(t_tnode *cursor)
{
	if (!cursor)
		return (NULL);
	else if (!cursor->left && cursor->type == COMMAND)
		return (cursor);
	else if (cursor->left)
		return (find_entry_astree(cursor->left));
	return (find_entry_astree(cursor->left));
}
