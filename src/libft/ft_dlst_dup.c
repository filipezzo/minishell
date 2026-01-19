/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:08:57 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/19 11:18:09 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlst_dup(t_dlist *src, void *(dup)(), void (*destroy)())
{
	t_dlist	*new;
	t_bnode	*node;

	if (!src)
		return (NULL);
	new = ft_new_dlist();
	if (!new)
		return (NULL);
	if (src->size == 0)
		return (new);
	node = src->head;
	while (node)
	{
		ft_add_nd_dlist(new, dup(node->data), destroy);
		node = node->right;
	}
	return (new);
}
