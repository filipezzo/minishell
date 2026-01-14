/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findin_bnode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:12:51 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/12 09:41:16 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Returns the node found from the equivalence function that compares the
 * information of each node in the doubly linked list until it finds the
 * equivalent.
 * @param list Doubly linked list used to find nodes that contain the specified
 * informations.
 * @param data Information retrieved from the list.
 * @param eq Function used to compare whether the information passed exists in
 * the list.
 * @return Returns the node found in the list, or null if it is not found, as
 * well as in case of error, null is returned.
 */
t_bnode	*ft_findin_dlist(t_dlist *list, void *data, t_bool (*eq)())
{
	t_bnode	*pivot;

	if (!list || !data || !eq)
		return (NULL);
	pivot = list->head;
	while (pivot && !eq(pivot->data, data))
		pivot = pivot->right;
	return (pivot);
}
