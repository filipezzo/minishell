/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 23:14:44 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/19 15:08:14 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_wildcard(char *src);
static void		expand_wildcards(t_dlist *names, t_tnode *node);

void	wildcard(t_astree *tree)
{
	t_dlist	*names;

	names = get_names_crrdir();
	expand_wildcards(names, tree->root);
	ft_destroy_dlist(names);
}

static void	expand_wildcards(t_dlist *names, t_tnode *node)
{
	size_t	i;
	char	**aux;

	if (!node)
		return ;
	if (node->type == COMMAND)
	{
		i = 1;
		while (get_cmd(node)->args[i])
		{
			if (is_wildcard(get_cmd(node)->args[i]))
			{
				aux = match_wildcard(names, get_cmd(node)->args, i);
				if (aux)
				{
					destroy_cmtx(get_cmd(node)->args);
					get_cmd(node)->args = aux;
				}
			}
			i++;
		}
	}
	expand_wildcards(names, node->left);
	expand_wildcards(names, node->right);
}

static t_bool	is_wildcard(char *src)
{
	size_t	last;
	t_bool	is_squote;
	t_bool	is_dquote;

	if (!src)
		return (FALSE);
	last = ft_strlen(src);
	is_squote = *src == '\'' && *(src + last) == '\'';
	is_dquote = *src == '\"' && *(src + last) == '\"';
	if (is_squote || is_dquote)
		return (FALSE);
	if (ft_strchr(src, '*') || ft_strchr(src, '?'))
		return (TRUE);
	return (FALSE);
}
