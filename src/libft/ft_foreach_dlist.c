/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach_dlist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:47:04 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/13 18:10:08 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_foreach_dlist(t_dlist *list, void *data, t_foreach_callback callback)
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
