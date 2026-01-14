/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:43:44 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/13 16:47:38 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	lex_squote(char **str, t_lextoken **unit);
static t_bool	lex_dquote(char **str, t_lextoken **unit);
static t_bool	lex_signs(char **str, t_lexsig **lexsig, t_lextoken **unit);
static t_bool	lex_word(char **str, t_lextoken **unit);

t_dlist	*lexer(char *in, t_lexsig **lexsig)
{
	t_dlist		*list;
	t_lextoken	*unit;
	char		*pivot;

	list = ft_new_dlist();
	pivot = in;
	while (*pivot)
	{
		while (*pivot && (*pivot == ' ' || *pivot == '\t'))
			pivot++;
		if (!*pivot)
			break ;
		if (lex_squote(&pivot, &unit))
			ft_add_nd_dlist(list, unit, destroy_lextoken);
		else if (lex_dquote(&pivot, &unit))
			ft_add_nd_dlist(list, unit, destroy_lextoken);
		else if (lex_signs(&pivot, lexsig, &unit))
			ft_add_nd_dlist(list, unit, destroy_lextoken);
		else if (lex_word(&pivot, &unit))
			ft_add_nd_dlist(list, unit, destroy_lextoken);
		else
			pivot++;
	}
	return (list);
}

static t_bool	lex_squote(char **str, t_lextoken **unit)
{
	const char	*start;
	char		*content;

	if (!*str || !**str)
		return (FALSE);
	if (**str != '\'' || !*str)
		return (FALSE);
	start = ++(*str);
	while (**str && **str != '\'')
		(*str)++;
	if (**str != '\'')
		return (pms_err("unexpected EOF while looking for matching \'", FALSE));
	content = ft_strndup(start, *str - start);
	if (!content)
		return (FALSE);
	if (!new_lextoken(unit, WORD, content))
		return (FALSE);
	(*str)++;
	return (TRUE);
}

static t_bool	lex_dquote(char **str, t_lextoken **unit)
{
	const char	*start;
	char		*content;

	if (!*str || !**str)
		return (FALSE);
	if (**str != '\"' || !*str)
		return (FALSE);
	start = (*str)++;
	while (**str)
	{
		if (**str == '\"' && (*str - start) > 0 && *(*str - 1) != '\\')
			break ;
		(*str)++;
	}
	if (**str != '\"')
		return (pms_err("unexpected EOF while looking for matching \"", FALSE));
	content = ft_strndup(start, *str - start + 1);
	if (!content)
		return (FALSE);
	if (!new_lextoken(unit, WORD, content))
		return (FALSE);
	(*str)++;
	return (TRUE);
}

static t_bool	lex_signs(char **str, t_lexsig **lexsig, t_lextoken **unit)
{
	size_t	i;
	char	*content;

	if (!*str || !**str)
		return (FALSE);
	if (!*str || !lexsig)
		return (FALSE);
	i = 0;
	while (lexsig[i] != NULL)
	{
		if (ft_strncmp(*str, lexsig[i]->sign, lexsig[i]->size) == 0)
		{
			content = ft_strndup(lexsig[i]->sign, lexsig[i]->size);
			if (!content)
				return (FALSE);
			if (!new_lextoken(unit, lexsig[i]->type, content))
				return (FALSE);
			(*str) += lexsig[i]->size;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static t_bool	lex_word(char **str, t_lextoken **unit)
{
	const char	*start;
	char		*content;

	if (!*str || !**str)
		return (FALSE);
	start = *str;
	while (**str && !lex_isjump(**str))
		(*str)++;
	if ((*str - start) == 0)
		return (FALSE);
	content = ft_strndup(start, *str - start);
	if (!content)
		return (FALSE);
	if (!new_lextoken(unit, WORD, content))
		return (FALSE);
	return (TRUE);
}
