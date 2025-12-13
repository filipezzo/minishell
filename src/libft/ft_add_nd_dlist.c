/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_nd_dlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:21:13 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/09 15:39:13 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Adds the node created from the information passed as a parameter, always 
 * placing it as the last element of the list, which is the tail of the doubly 
 * linked list. If the list is still empty, the node will become both the head 
 * and tail.
 * @param list Data structure doubly linked list where the node will be placed.
 * @param data Node information.
 * @param dst_dt Function used to destroy the information of the created 
 * node from the allocated memory.
 * @return Returns the same list to which the created node was added.
 */
t_dlist	*ft_add_nd_dlist(t_dlist *list, void *data, destroy dst_dt)
{
	t_bnode	*node;

	if (!list || !data || !dst_dt)
		return (NULL);
	node = ft_new_bnode(data, list, dst_dt);
	if (!node)
		return (NULL);
	if (!list->head || !list->tail)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		ft_setdir_bnode(node, NULL, list->tail);
		ft_setdir_bnode(list->tail, node, list->tail->prev);
		list->tail = node;
	}
	list->size += 1;
	return (list);
}
