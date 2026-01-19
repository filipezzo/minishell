/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 00:22:26 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/19 11:16:19 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool iseq_list_and_cmtx(t_dlist *list, char **mtx)
{
	size_t	i;
	t_bnode	*cursor;

	if (!list || !mtx)
		return (FALSE);
	i = 0;
	cursor = list->head;
	while (cursor && mtx[i])
	{
		if (ft_strcmp((char *)cursor->data, mtx[i]) != 0)
			return (FALSE);
		cursor = cursor->right;
		i++;
	}
	return (TRUE);
}

char	**convert_lst_to_cmtx(t_dlist *list)
{
	size_t	i;
	t_bnode	*cursor;
	char	**cmtx;

	if (!list || (list && list->size == 0))
		return (NULL);
	cmtx = ft_calloc(list->size + 1, sizeof(char *));
	if (!cmtx)
		return (NULL);
	i = 0;
	cursor = list->head;
	while (cursor)
	{
		cmtx[i] = ft_strdup(cursor->data);
		cursor = cursor->right;
		i++;
	}
	if (!iseq_list_and_cmtx(list, cmtx))
	{
		destroy_cmtx(cmtx);
		return (NULL);
	}
	return (cmtx);
}

t_dlist	*convert_cmtx_to_lst(char **cmtx)
{
	size_t	i;
	t_dlist	*list;

	if (!cmtx)
		return (NULL);
	list = ft_new_dlist();
	i = 0;
	while (cmtx[i])
	{
		ft_add_nd_dlist(list, ft_strdup(cmtx[i]), free);
		i++;
	}
	if (!iseq_list_and_cmtx(list, cmtx))
	{
		ft_destroy_dlist(list);
		return (NULL);
	}
	return (list);
}
