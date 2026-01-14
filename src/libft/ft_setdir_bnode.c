/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setdir_bnode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:21:23 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/13 18:07:27 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_setdir_bnode(t_bnode *node, t_bnode *left, t_bnode *right)
{
	if (!node)
		return (FALSE);
	node->left = left;
	node->right = right;
	return (TRUE);
}
