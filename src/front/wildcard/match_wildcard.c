/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:23:40 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/24 11:15:07 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_dlist	*match_to_names(t_dlist *names, char *wildcard);
static t_bool	ismatch_wildcard(char *name, char *pattern);
static t_bool	ignore_name(char *name, char *wildcard);
static void		*helper_destroy(t_dlist *list);

char	**match_wildcard(t_dlist *names, char **args, size_t itgt)
{
	t_dlist	*match;
	t_dlist	*new_lst;
	char	**new;

	match = match_to_names(names, args[itgt]);
	if (!match || match->size == 0)
		return (helper_destroy(match));
	ft_sort_dlist(match, ASC_SORT, ft_wrp_strcmp);
	new_lst = convert_cmtx_to_lst(args);
	if (!new_lst)
		return (helper_destroy(match));
	if (!expand_args_at(new_lst, match, itgt))
	{
		ft_destroy_dlist(match);
		ft_destroy_dlist(new_lst);
		return (NULL);
	}
	new = convert_lst_to_cmtx(new_lst);
	ft_destroy_dlist(match);
	ft_destroy_dlist(new_lst);
	return (new);
}

static t_dlist	*match_to_names(t_dlist *names, char *wildcard)
{
	t_bnode	*node;
	t_dlist	*match;

	if (!names || !wildcard)
		return (NULL);
	match = ft_new_dlist();
	node = names->head;
	while (node)
	{
		if (!ignore_name((char *)node->data, wildcard)
			&& ismatch_wildcard((char *)node->data, wildcard))
			ft_add_nd_dlist(match, ft_strdup(node->data), free);
		node = node->right;
	}
	if (match->size == 0)
	{
		ft_destroy_dlist(match);
		return (NULL);
	}
	return (match);
}

static t_bool	ismatch_wildcard(char *name, char *pattern)
{
	if (*pattern == '\0')
		return (*name == '\0');
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (*pattern == '\0')
			return (TRUE);
		while (*name)
		{
			if (ismatch_wildcard(name, pattern))
				return (TRUE);
			name++;
		}
		return (FALSE);
	}
	if (*pattern == '?')
	{
		if (*name == '\0')
			return (FALSE);
		return (ismatch_wildcard(name + 1, pattern + 1));
	}
	if (*name == *pattern)
		return (ismatch_wildcard(name + 1, pattern + 1));
	return (FALSE);
}

static t_bool	ignore_name(char *name, char *wildcard)
{
	return (*name == '.' && *wildcard != '.');
}

static void	*helper_destroy(t_dlist *list)
{
	ft_destroy_dlist(list);
	return (NULL);
}
