/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_astree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:45:33 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/16 11:47:45 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_astree	*ft_new_astree(void)
{
	t_astree	*tree;

	tree = malloc(sizeof(t_astree));
	if (!tree)
		return (NULL);
	tree->root = NULL;
	tree->leaves = 0;
	return (tree);
}
