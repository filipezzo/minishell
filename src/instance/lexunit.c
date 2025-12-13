
#include "minishell.h"

t_bool	new_lexunit(t_lexunit **new, t_type type, char *content)
{
	*new = malloc(sizeof(t_lexunit));
	if (!new)
		return (FALSE);
	(*new)->type = WORD;
	if (type)
		(*new)->type = type;
	content = NULL;
	if (content)
		(*new)->content = content;
	return (TRUE);
}

t_bool	destroy_lexunit(void *ptr)
{
	t_lexunit	*lex_unit;

	if (!ptr)
		return (FALSE);
	lex_unit = (t_lexunit *)ptr;
	free(lex_unit->content);
	free(lex_unit);
	return (TRUE);
}
