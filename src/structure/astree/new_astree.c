/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_astree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:10:57 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/07 17:14:37 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_astree	*new_astree(void)
{
	t_astree	*tree;

	tree = ft_calloc(1, sizeof(t_astree));
	if (!tree)
		return (NULL);
	tree->mstype = ASTREE_T;
	tree->root = NULL;
	tree->entry = NULL;
	return (tree);
}
