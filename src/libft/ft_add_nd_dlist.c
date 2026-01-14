/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_nd_dlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 09:38:44 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/13 18:10:50 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_add_nd_dlist(t_dlist *list, void *data, t_destroy dst)
{
	t_bnode	*node;

	if (!list || !data || !dst)
		return (NULL);
	node = ft_new_bnode(data, list, dst);
	if (!node)
		return (NULL);
	if (!list->head || !list->tail)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		ft_setdir_bnode(node, list->tail, NULL);
		ft_setdir_bnode(list->tail, list->tail->left, node);
		list->tail = node;
	}
	list->size += 1;
	return (list);
}
