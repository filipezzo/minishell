/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indexof_dlist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 22:31:00 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/20 01:44:33 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_bnode	*travel_back(t_bnode **node, size_t size, size_t idx);
static t_bnode	*travel_front(t_bnode **node, size_t size, size_t idx);

t_bnode	*ft_indexof_dlist(t_dlist *list, size_t idx)
{
	t_bnode	*node;

	if (!list || idx >= list->size)
		return (NULL);
	if (idx > (list->size / 2))
	{
		node = list->tail;
		travel_back(&node, list->size, idx);
	}
	else
	{
		node = list->head;
		travel_front(&node, list->size, idx);
	}
	return (node);
}

static t_bnode	*travel_back(t_bnode **node, size_t size, size_t idx)
{
	size_t	i;

	i = size - 1;
	while (i > idx)
	{
		i--;
		*node = (*node)->left;
	}
}

static t_bnode	*travel_front(t_bnode **node, size_t size, size_t idx)
{
	size_t	i;

	i = 0;
	while (i < idx)
	{
		i++;
		*node = (*node)->right;
	}
}
