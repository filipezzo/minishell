/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_dlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:41:00 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/23 17:34:00 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		quick(t_bnode *first, t_bnode *last, t_sort dir, int (*cmp)());
static t_bnode	*asc_sort(t_bnode *first, t_bnode *last, int (*cmp)());
static t_bnode	*desc_sort(t_bnode *first, t_bnode *last, int (*cmp)());
static void		check_to_swap(t_bnode *n1, t_bnode *n2);

t_bool	ft_sort_dlist(t_dlist *list, t_sort dir, int (*cmp)())
{
	t_bool	exit_direction;

	exit_direction = !(dir >= ASC_SORT && dir <= DESC_SORT);
	if (!list || exit_direction || list->size < 2)
		return (FALSE);
	quick(list->head, list->tail, dir, cmp);
	return (TRUE);
}

static void	quick(t_bnode *first, t_bnode *last, t_sort dir, int (*cmp)())
{
	t_bnode	*pivot;

	if (!first || !last || first == last || last->right == first)
		return ;
	if (dir == ASC_SORT)
		pivot = asc_sort(first, last, cmp);
	else
		pivot = desc_sort(first, last, cmp);
	if (pivot && pivot->left)
		quick(first, pivot->left, dir, cmp);
	if (pivot && pivot->right)
		quick(pivot->right, last, dir, cmp);
}

static t_bnode	*asc_sort(t_bnode *first, t_bnode *last, int (*cmp)())
{
	t_bnode	*pivot;
	t_bnode	*i;
	t_bnode	*j;

	pivot = last;
	i = first->left;
	j = first;
	while (j != last)
	{
		if (cmp(j->data, pivot->data) <= 0)
		{
			if (i == NULL)
				i = first;
			else
				i = i->right;
			ft_swap(&i->data, &j->data);
		}
		j = j->right;
	}
	if (i == NULL)
		i = first;
	else
		i = i->right;
	check_to_swap(i, last);
	return (i);
}

static t_bnode	*desc_sort(t_bnode *first, t_bnode *last, int (*cmp)())
{
	t_bnode	*pivot;
	t_bnode	*i;
	t_bnode	*j;

	pivot = last;
	i = first->left;
	j = first;
	while (j != last)
	{
		if (cmp(j->data, pivot->data) >= 0)
		{
			if (i == NULL)
				i = first;
			else
				i = i->right;
			ft_swap(&i->data, &j->data);
		}
		j = j->right;
	}
	if (i == NULL)
		i = first;
	else
		i = i->right;
	check_to_swap(i, last);
	return (i);
}

static void	check_to_swap(t_bnode *n1, t_bnode *n2)
{
	if (n1 != n2)
		ft_swap(&n1->data, &n2->data);
}
