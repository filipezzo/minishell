/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:43:44 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/28 19:12:45 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	lex_single_quote(char **str, t_lexunit **unit);
static t_bool	lex_double_quote(char **str, t_lexunit **unit);
static t_bool	lex_signs(char **str, t_siglexer **siglexer, t_lexunit **unit);
static t_bool	lex_word(char **str, t_lexunit **unit);

t_dlist	*lexer(char *in, t_siglexer **siglex)
{
	t_dlist		*list;
	t_lexunit	*unit;
	char		*pivot;

	list = ft_new_dlist();
	pivot = in;
	while (*pivot)
	{
		while (*pivot && (*pivot == ' ' || *pivot == '\t'))
			pivot++;
		if (lex_single_quote(&pivot, &unit))
			ft_add_nd_dlist(list, unit, destroy_lexunit);
		else if (lex_double_quote(&pivot, &unit))
			ft_add_nd_dlist(list, unit, destroy_lexunit);
		else if (lex_signs(&pivot, siglex, &unit))
			ft_add_nd_dlist(list, unit, destroy_lexunit);
		else if (lex_word(&pivot, &unit))
			ft_add_nd_dlist(list, unit, destroy_lexunit);
	}
	return (list);
}

static t_bool	lex_single_quote(char **str, t_lexunit **unit)
{
	const char	*start;

	if (!*str || !**str)
		return (FALSE);
	if (**str != '\'' || !*str)
		return (FALSE);
	start = ++(*str);
	while (**str && **str != '\'')
		(*str)++;
	if (**str != '\'')
	{
		ft_putstr_fd("unexpected EOF while looking for matching \'\n",
			STDERR_FILENO);
		return (FALSE);
	}
	if (!new_lexunit(unit, WORD, NULL))
		return (FALSE);
	(*unit)->type = WORD;
	(*unit)->content = ft_strndup(start, *str - start);
	(*str)++;
	return (TRUE);
}

static t_bool	lex_double_quote(char **str, t_lexunit **unit)
{
	const char	*start;

	if (!*str || !**str)
		return (FALSE);
	if (**str != '\"' || !*str)
		return (FALSE);
	start = ++(*str);
	while (**str && **str != '\"')
		(*str)++;
	if (**str != '\"')
	{
		ft_putstr_fd("unexpected EOF while looking for matching \"\n",
			STDERR_FILENO);
		return (FALSE);
	}
	if (!new_lexunit(unit, WORD, NULL))
		return (FALSE);
	(*unit)->type = WORD;
	(*unit)->content = ft_strndup(start, *str - start);
	(*str)++;
	return (TRUE);
}

static t_bool	lex_signs(char **str, t_siglexer **siglex, t_lexunit **unit)
{
	size_t	i;

	if (!*str || !**str)
		return (FALSE);
	if (!*str || !siglex)
		return (FALSE);
	i = 0;
	while (siglex[i] != NULL)
	{
		if (ft_strncmp(*str, siglex[i]->sign, siglex[i]->size) == 0)
		{
			if (!new_lexunit(unit, WORD, NULL))
				return (FALSE);
			(*unit)->type = siglex[i]->type;
			(*unit)->content = ft_strndup(siglex[i]->sign, siglex[i]->size);
			(*str) += siglex[i]->size;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static t_bool	lex_word(char **str, t_lexunit **unit)
{
	const char	*start;

	if (!*str || !**str)
		return (FALSE);
	start = *str;
	while (**str && !lex_isjump(**str))
		(*str)++;
	if ((*str - start) == 0)
		return (FALSE);
	if (!new_lexunit(unit, WORD, NULL))
		return (FALSE);
	(*unit)->content = ft_strndup(start, *str - start);
	if (!(*unit)->content)
		return (FALSE);
	(*unit)->type = WORD;
	return (TRUE);
}
