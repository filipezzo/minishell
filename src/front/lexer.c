
#include "minishell.h"

static t_bool	lex_single_quote(char **str, t_lexunit *unit);
static t_bool	lex_double_quote(char **str, t_lexunit *unit);
static t_bool	lex_signs(char **str, t_siglexer **siglexer, t_lexunit *unit);
static t_bool	lex_word(char **str, t_lexunit *unit);

t_dlist	*lexer(char *in, t_siglexer **siglex)
{
	t_dlist		*list;
	t_lexunit	*unit;
	char		*pivot;

	list = ft_new_dlist();
	pivot = in;
	while (*pivot)
	{
		if (!new_lexunit(&unit, WORD, NULL))
			return (NULL);
		while (pivot && (pivot == ' ' || pivot == '\t'))
			pivot++;
		if (lex_single_quote(&pivot, unit))
			ft_add_nd_dlist(list, unit, destroy_lexunit);
		else if (lex_double_quote(&pivot, unit))
			ft_add_nd_dlist(list, unit, destroy_lexunit);
		else if (lex_signs(&pivot, siglex, unit))
			ft_add_nd_dlist(list, unit, destroy_lexunit);
		else if (lex_word(&pivot, unit))
			ft_add_nd_dlist(list, unit, destroy_lexunit);
	}
	return (list);
}

static t_bool	lex_single_quote(char **str, t_lexunit *unit)
{
	const char	*start;

	if (**str != '\'' || !*str || !unit)
		return (FALSE);
	start = ++(*str);
	while (**str && **str != '\'')
		(*str)++;
	if (**str != '\'')
		return (FALSE);
	unit->type = WORD;
	unit->content = ft_strndup(start, *str - start);
	(*str)++;
	return (TRUE);
}

static t_bool	lex_double_quote(char **str, t_lexunit *unit)
{
	const char	*start;

	if (**str != '\"' || !*str || !unit)
		return (FALSE);
	start = ++(*str);
	while (**str && **str != '\"')
		(*str)++;
	if (**str != '\"')
		return (FALSE);
	unit->type = WORD;
	unit->content = ft_strndup(start, *str - start);
	(*str)++;
	return (TRUE);
}

static t_bool	lex_signs(char **str, t_siglexer **siglex, t_lexunit *unit)
{
	size_t	i;

	if (!*str || !siglex || !unit)
		return (FALSE);
	i = 0;
	while (siglex[i] != NULL)
	{
		if (ft_strncmp(*str, siglex[i]->sign, siglex[i]->size) == 0)
		{
			unit->type = siglex[i]->type;
			unit->content = ft_strndup(siglex[i]->sign, siglex[i]->size);
			(*str) += siglex[i]->size;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static t_bool	lex_word(char **str, t_lexunit *unit)
{
	const char	*start;

	if (!*str || !unit)
		return (FALSE);
	start = *str;
	while (**str && !lex_isjump(**str))
		(*str)++;
	if ((*str - start) == 0)
		return (FALSE);
	unit->content = ft_strndup(start, *str - start);
	if (!unit->content)
		return (FALSE);
	unit->type = WORD;
	return (TRUE);
}
