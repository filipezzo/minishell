/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setdir_bnode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:21:23 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/13 17:31:18 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Refers to the navigation directions of the specified node. 
 * @param node Node that will be referenced by the directions.
 * @param right Navigation reference from the right node to this one.
 * @param left Navigation reference from the left node to this one.
 * @return If the specified node exists, it is possible to assign the 
 * directions, ans true will be returned; otherwise, false will be returned.
 */
t_bool	ft_setdir_bnode(t_bnode *node, t_bnode *left, t_bnode *right)
{
	if (!node)
		return (FALSE);
	node->left = left;
	node->right = right;
	return (TRUE);
}
