/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_nd_dlist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:35:38 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/09 17:52:57 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Removes a node from the doubly linked list.
 * @param list List containing the node to be removed.
 * @param tgt Target node that should be removed from the list.
 * @return Returns the same list with the target node no longer among its 
 * elements.
 */
t_dlist	*ft_remove_nd_dlist(t_dlist *list, t_bnode *tgt)
{
	if (!list || !tgt)
		return (NULL);
	if (tgt->prev)
		tgt->prev->next = tgt->next;
	else
		list->head = tgt->next;
	if (tgt->next)
		tgt->next->prev = tgt->prev;
	else
		list->tail = tgt->prev;
	ft_destroy_bnode(tgt);
	list->size -= 1;
	return (list);
}
