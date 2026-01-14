/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findin_bnode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:12:51 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/13 18:10:18 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
