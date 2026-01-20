/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilex_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:42:40 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/20 17:44:34 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	helper_dollar_expander(t_dlist *tokens, char *start, char **end);

void	minilexer_expand(t_dlist *tokens, char *src)
{
	char	*start;
	char	*end;

	end = src;
	while (*end)
	{
		start = end;
		if (*end == '$')
			helper_dollar_expander(tokens, start, &end);
		else
		{
			while (*end && *end != '$')
				end++;
			ft_add_nd_dlist(tokens, ft_substr(start, 0, end - start), free);
		}
	}
}

static void	helper_dollar_expander(t_dlist *tokens, char *start, char **end)
{
	(*end)++;
	if (!**end)
	{
		ft_add_nd_dlist(tokens, ft_strdup("$"), free);
		return ;
	}
	else if (ft_strchr("_$?0123456789", **end))
	{
		if (**end == '_')
			ft_add_nd_dlist(tokens, ft_strdup("$_"), free);
		else if (**end == '$')
			ft_add_nd_dlist(tokens, ft_strdup("$$"), free);
		else if (**end == '?')
			ft_add_nd_dlist(tokens, ft_strdup("$?"), free);
		else if (ft_isdigit(**end))
			ft_add_nd_dlist(tokens, ft_substr(start, 0, 2), free);
		(*end)++;
	}
	else
	{
		while (**end && (ft_isalnum(**end) || **end == '_'))
			(*end)++;
		ft_add_nd_dlist(tokens, ft_substr(start, 0, *end - start), free);
	}
}
