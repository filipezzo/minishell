/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_bnode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:55:06 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/07 11:55:51 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Creates a node with bidirectional navigation pointers. Initially loose, not
 * directed to any node.
 * @param data Node information.
 * @param structure Reference to the data structure to which the node belongs.
 * @param dst Reference to the function destroy data.
 * @return Memory-allocated node.
 */
t_bnode	*ft_new_bnode(void *data, void *structure, destroy dst)
{
	t_bnode	*node;

	if (!data)
		return (NULL);
	node = ft_calloc(1, sizeof(t_bnode));
	if (!node)
		return (NULL);
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->structure = structure;
	node->destroy_data = dst;
	return (node);
}
