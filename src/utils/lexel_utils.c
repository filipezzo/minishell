
#include "minishell.h"

t_bool	lex_isjump(char c)
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
