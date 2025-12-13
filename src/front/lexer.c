
#include "minishell.h"

static void	skip_spaces(char **str)
{
	while (**str && (**str == ' ' || **str == '\t'))
		(*str)++;
}

static t_bool	cut_single_quote(char **str, t_lexunit *token)
{
	const char	*start;

	if (**str != '\'' || !*str || !token)
		return (FALSE);
	start = ++(*str);
	while (**str && **str != '\'')
		(*str)++;
	if (**str != '\'')
		return (FALSE);
	token->type = WORD;
	token->content = ft_strndup(start, *str - start);
	(*str)++;
	return (TRUE);
}

static t_bool	cut_double_quote(char **str, t_lexunit *token)
{
	const char	*start;

	if (**str != '\"' || !*str || !token)
		return (FALSE);
	start = ++(*str);
	while (**str && **str != '\"')
		(*str)++;
	if (**str != '\"')
		return (FALSE);
	token->type = WORD;
	token->content = ft_strndup(start, *str - start);
	(*str)++;
	return (TRUE);
}

static t_bool	cut_signs(char **str, t_siglexer **siglexer, t_lexunit *token)
{
	size_t	i;

	if (!*str || !siglexer || !token)
		return (FALSE);
	i = 0;
	while (siglexer[i] != NULL)
	{
		if (ft_strncmp(*str, siglexer[i]->sign, siglexer[i]->size) == 0)
		{
			token->type = siglexer[i]->type;
			token->content = ft_strndup(siglexer[i]->sign, siglexer[i]->size);
			(*str) += siglexer[i]->size;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static t_bool	is_jump_word(char c)
{
	char	*signs;
	size_t	i;

	if (ft_isspace(c))
		return (TRUE);
	if (c == '\'' || c == '\"')
		return (TRUE);
	signs = "|&;()<>";
	i = 0;
	while (signs[i] && c != signs[i])
		i++;
	if (c == signs[i])
		return (TRUE);
	return (FALSE);
}

static t_bool	cut_word(char **str, t_lexunit *token)
{
	const char	*start;

	if (!*str || !token)
		return (FALSE);
	start = *str;
	while (**str && !is_jump_word(**str))
		(*str)++;
	if ((*str - start) == 0)
		return (FALSE);
	token->content = ft_strndup(start, *str - start);
	if (!token->content)
		return (FALSE);
	token->type = WORD;
	return (TRUE);
}

t_dlist	*lexer(char *in, t_siglexer **siglexer)
{
	t_dlist		*list;
	t_lexunit	*unit;
	char		*pivot;

	list = ft_new_dlist(ft_destroy_bnode);
	pivot = in;
	while (*pivot)
	{
		unit = malloc(sizeof(t_lexunit));
		if (!unit)
			return (NULL);
		skip_spaces(&pivot);
		if (cut_single_quote(&pivot, unit))
			ft_add_nd_dlist(list, unit, destroy_lexunit);
		else if (cut_double_quote(&pivot, unit))
			ft_add_nd_dlist(list, unit, destroy_lexunit);
		else if (cut_signs(&pivot, siglexer, unit))
			ft_add_nd_dlist(list, unit, destroy_lexunit);
		else if (cut_word(&pivot, unit))
			ft_add_nd_dlist(list, unit, destroy_lexunit);
	}
	return (list);
}
