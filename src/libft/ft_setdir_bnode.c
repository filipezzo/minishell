/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setdir_bnode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:21:23 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/09 12:17:59 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Refers to the navigation directions of the specified node. 
 * @param node Node that will be referenced by the directions.
 * @param next Navigation reference from the next node to this one.
 * @param prev Navigation reference for the node preceding this one.
 * @return If the specified node exists, it is possible to assign the 
 * directions, ans true will be returned; otherwise, false will be returned.
 */
t_bool	ft_setdir_bnode(t_bnode *node, t_bnode *next, t_bnode *prev)
{
	if (!node)
		return (FALSE);
	node->next = next;
	node->prev = prev;
	return (TRUE);
}
