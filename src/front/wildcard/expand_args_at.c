/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_at.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:56:23 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/19 11:16:05 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	check_go_to_target(t_bnode **node, size_t itgt);

t_dlist	*expand_args_at(t_dlist *dst, t_dlist *src, size_t itgt)
{
	t_dlist	*cpy;
	t_bnode	*node;

	if (!dst || !src)
		return (NULL);
	if (src->size == 0)
		return (dst);
	node = dst->head;
	if (!check_go_to_target(&node, itgt))
		return (NULL);
	cpy = ft_dlst_dup(src, ft_wrp_strdup, free);
	if (node->left)
		node->left->right = cpy->head;
	else
		dst->head = cpy->head;
	cpy->head->left = node->left;
	if (node->right)
		node->right->left = cpy->tail;
	else
		dst->tail = cpy->tail;
	cpy->tail->right = node->right;
	dst->size = dst->size + cpy->size - 1;
	ft_destroy_bnode(node);
	free(cpy);
	return (dst);
}

static t_bool	check_go_to_target(t_bnode **node, size_t itgt)
{
	size_t	i;

	if (!*node)
		return (FALSE);
	i = 0;
	while (*node && i != itgt)
	{
		*node = (*node)->right;
		i++;
	}
	if (i < itgt || i > itgt)
		return (FALSE);
	return (TRUE);
}
