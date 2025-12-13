/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach_dlist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:47:04 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/13 17:28:54 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Iterate throught the double linked list by applying the function to the 
 * information.
 * @param list Double linked list used used for the application for each element 
 * that composes it using the callback function.
 * @param data Information.
 * @param callback Execution function for the information passed.
 * @return True if you managed to go through the entire list and apply the 
 * procedure, and false if you did not.
 */
t_bool	ft_foreach_dlist(t_dlist *list, void *data, foreach_callback callback)
{
	t_bnode	*pivot;

	if (!list || !callback)
		return (FALSE);
	pivot = list->head;
	while (pivot)
	{
		if (callback(pivot->data, data) == FALSE)
			return (FALSE);
		pivot = pivot->right;
	}
	return (TRUE);
}
