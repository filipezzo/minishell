/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_dlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:52:13 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/09 13:26:52 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Creates a double-linked list.
 * @param destroy_node Pointer to the function used to destroy a node using the 
 * data as a parameter to found him.
 * @return New double-linked list allocated in the heap memory.
 */
t_dlist	*ft_new_dlist(t_bool (*destroy_nd)())
{
	t_dlist	*list;

	list = malloc(sizeof(t_dlist));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	list->destroy_node = destroy_nd;
	return (list);
}
