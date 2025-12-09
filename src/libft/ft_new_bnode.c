/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_bnode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:55:06 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/09 16:04:03 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Creates a node with bidirectional navigation pointers. Initially loose, not 
 * directed to any node.
 * @param data Node information.
 * @param structure Reference to the data structure to which the node belongs.
 * @param dst_dt Reference to the function destroy data.
 * @return Memory-allocated node.
 */
t_bnode	*ft_new_bnode(void *data, void *structure, destroy dst_dt)
{
	t_bnode	*node;

	if (!data)
		return (NULL);
	node = malloc(sizeof(t_bnode));
	if (!node)
		return (NULL);
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	node->structure = structure;
	node->destroy_data = dst_dt;
	return (node);
}
