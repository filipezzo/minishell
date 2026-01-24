/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy_bnode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:23:37 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/13 18:10:37 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_destroy_bnode(void *ptr)
{
	t_bnode	*node;

	if (!ptr || !((t_bnode *)ptr)->destroy_data)
		return (FALSE);
	node = (t_bnode *)ptr;
	if (node->destroy_data)
		node->destroy_data(node->data);
	free(node);
	return (TRUE);
}
