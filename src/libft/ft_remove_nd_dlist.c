/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_nd_dlist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:35:38 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/13 18:07:31 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_remove_nd_dlist(t_dlist *list, t_bnode *tgt)
{
	if (!list || !tgt)
		return (NULL);
	if (tgt->left)
		tgt->left->right = tgt->right;
	else
		list->head = tgt->right;
	if (tgt->right)
		tgt->right->left = tgt->left;
	else
		list->tail = tgt->left;
	ft_destroy_bnode(tgt);
	if (list->size > 0)
		list->size -= 1;
	return (list);
}
