/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy_dlist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:41:50 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/13 16:42:05 by mhidani          ###   ########.fr       */
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
	size_t	i;

	if (!ptr)
		return (FALSE);
	list = (t_dlist *)ptr;
	pivot = list->head;
	i = 0;
	while (pivot && i < list->size)
	{
		next = pivot->next;
		if (ft_destroy_bnode(pivot) == FALSE)
			break;
		i++;
		pivot = next;
		list->head = pivot;
	}
	if (i != list->size)
		return (FALSE);
	free(list);
	return (TRUE);
}
