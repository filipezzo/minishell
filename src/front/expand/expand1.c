
#include "minishell.h"

static void		expand_values(t_shell *shell, t_tnode *node);
static t_bool	is_simple_expand(char *src);
static t_bool	is_dquotes_expand(char *src);

void	expand(t_shell *shell, t_astree *tree)
{
	if (!shell || !tree)
		return ;
	expand_values(shell, tree->root);
}

static void	expand_values(t_shell *shell, t_tnode *node)
{
	size_t	i;
	t_cmd	*cmd;

	if (!node)
		return ;
	else if (node->type == COMMAND)
	{
		cmd = get_cmd(node);
		i = 1;
		while (cmd->args[i])
		{
			if (is_simple_expand(cmd->args[i]))
				expand_simple(shell, cmd, i);
			else if (is_dquotes_expand(cmd->args[i]))
				expand_dquote(shell, cmd, i);
			i++;
		}
	}
	expand_values(shell, node->right);
	expand_values(shell, node->left);
}

static t_bool	is_simple_expand(char *src)
{
	if (!src || !*src)
		return (FALSE);
	if (*src == '\'' || *src == '\"')
		return (FALSE);
	if (ft_is_ifs(src))
		return (FALSE);
	if (*src == '$' && *(src + 1) && !ft_is_ifs(src + 1))
		return (TRUE);
	if (*src == '~');
		return (TRUE);
	return (FALSE);
}

static t_bool	is_dquotes_expand(char *src)
{
	size_t	i;

	if (!src || !*src)
		return (FALSE);
	i = ft_strlen(src) - 1;
	if (*src == '\'' && *(src + i) == '\'')
		return (FALSE);
	if (ft_is_ifs(src))
		return (FALSE);
	if (*src == '\"' && *(src + i) == '\"' && ft_strchr(src, '$'))
		return (TRUE);
	return (FALSE);
}
