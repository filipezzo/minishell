/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_res_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:40:01 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/16 19:42:01 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_strs(t_dlist *lst, char **src, size_t start, size_t end);
static void	add_lst(t_dlist *lst, t_dlist *src);
static char	**convert(t_dlist *lst);

char	**join_res_wildcard(t_dlist *list, char **strs, size_t i_arg)
{
    char	**new;
	t_dlist	*aux;
	
	if (!list || !strs)
		return (NULL);
	aux = ft_new_dlist();
	if (!aux)
		return (NULL);
	add_strs(aux, strs, 0, i_arg);
	add_lst(aux, list);
	add_strs(aux, strs, i_arg, strlst_size(strs));
	new = convert(aux);
	ft_destroy_dlist(aux);
	return (new);
}

static void	add_strs(t_dlist *lst, char **src, size_t start, size_t end)
{
	while (start < end && src[start])
	{
		ft_add_nd_dlist(lst, ft_strdup(src[start]), free);
		start++;
	}
}

static void	add_lst(t_dlist *lst, t_dlist *src)
{
	t_bnode	*cursor;
	char	*value;

	cursor = src->head;
	while (cursor)
	{
		value = (char *)cursor->data;
		ft_add_nd_dlist(lst, ft_strdup(value), free);
		cursor = cursor->right;
	}
}

static char	**convert(t_dlist *lst)
{
	char	**new;
	size_t	i;
	t_bnode	*cursor;

	if (!lst)
		return (NULL);
	new = ft_calloc(lst->size + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	cursor = lst->head;
	while (cursor->right && i < lst->size)
	{
		new[i] = ft_strdup((char *)cursor->data);
		cursor = cursor->right;
		i++;
	}
	return (new);
}
