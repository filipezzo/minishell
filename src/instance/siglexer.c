
#include "minishell.h"

t_siglexer	*new_siglexer(t_type type, char *sign, size_t size)
{
	t_siglexer	*siglexer;

	siglexer = malloc(sizeof(t_siglexer));
	if (!siglexer)
		return (NULL);
	siglexer->type = type;
	siglexer->sign = sign;
	siglexer->size = size;
	return (siglexer);
}

t_bool	destroy_siglexer(void *ptr)
{
	if (!ptr)
		return (FALSE);
	free(ptr);
	return (TRUE);
}

t_siglexer	**new_lst_siglexer(void)
{
	t_siglexer	**signs;
	size_t		size;

	size = 12;
	signs = ft_calloc(size + 1, sizeof(t_siglexer *));
	if (!signs)
		return (NULL);
	signs[0] = new_siglexer(REDIR_APPEND, ">>", 2);
	signs[1] = new_siglexer(REDIR_HEREDOC, "<<", 2);
	signs[2] = new_siglexer(AND_IF, "&&", 2);
	signs[3] = new_siglexer(AND_OR, "||", 2);
	signs[4] = new_siglexer(REDIR_IN, "<", 1);
	signs[5] = new_siglexer(REDIR_OUT, ">", 1);
	signs[6] = new_siglexer(PIPE, "|", 1);
	signs[7] = new_siglexer(LPAREN, "(", 1);
	signs[8] = new_siglexer(RPAREN, ")", 1);
	signs[9] = new_siglexer(RUN_BKG, "&", 1);
	signs[10] = new_siglexer(CMD_SEP, ";", 1);
	signs[11] = NULL;
	return (signs);
}

t_bool	destroy_lst_siglexer(void *ptr)
{
	t_siglexer	**signs;
	size_t		i;

	if (!ptr)
		return (FALSE);
	signs = (t_siglexer **)ptr;
	i = 0;
	while (signs[i])
	{
		free(signs[i]);
		i++;
	}
	free(signs);
	return (TRUE);
}
