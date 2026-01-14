/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_bnode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:55:06 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/13 18:07:51 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bnode	*ft_new_bnode(void *data, void *structure, t_destroy dst)
{
	t_bnode	*node;

	if (!data)
		return (NULL);
	node = ft_calloc(1, sizeof(t_bnode));
	if (!node)
		return (NULL);
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->structure = structure;
	node->destroy_data = dst;
	return (node);
}
