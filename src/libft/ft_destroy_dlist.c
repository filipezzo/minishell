/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy_dlist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:41:50 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/07 16:10:17 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Destroy the doubly linked list with all its nodes. If the operation cannot be
 * performed, false will be returned (The list was not destroyed).
 * @param ptr Pointer reference to the doubly linked list.
 * @return True if the destruction process was successful, and false if it was
 * not possible to destroy the list, which remains allocated in memory.
 */
t_bool	ft_destroy_dlist(void *ptr)
{
	t_dlist	*list;
	t_bnode	*pivot;
	t_bnode	*next;

	if (!ptr)
		return (FALSE);
	list = (t_dlist *)ptr;
	pivot = list->head;
	while (pivot)
	{
		next = pivot->right;
		ft_destroy_bnode(pivot);
		pivot = next;
	}
	list->size = 0;
	free(list);
	return (TRUE);
}
