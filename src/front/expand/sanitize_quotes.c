/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:48:15 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/21 15:49:25 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	navast_change_commands(t_tnode *node);
static char	*handle_sanitize_quotes(char *src);

void	sanitize_quotes(t_astree *tree)
{
	if (!tree || !tree->root)
		return ;
	navast_change_commands(tree->root);
}

static void	navast_change_commands(t_tnode *node)
{
	size_t	i;
	t_cmd	*cmd;
	char	*aux;

	if (!node)
		return ;
	if (node->type == COMMAND && get_cmd(node)->args)
	{
		i = 0;
		cmd = get_cmd(node);
		while (cmd->args[i])
		{
			aux = handle_sanitize_quotes(cmd->args[i]);
			if (!aux)
			{
				i++;
				continue ;
			}
			free(cmd->args[i]);
			cmd->args[i] = aux;
			i++;
		}
	}
	navast_change_commands(node->left);
	navast_change_commands(node->right);
}

static char	*handle_sanitize_quotes(char *src)
{
	size_t	size;
	t_bool	is_squotes;
	t_bool	is_dquotes;
	char	*new;

	if (!src)
		return (NULL);
	size = ft_strlen(src);
	if (size < 2)
		return (NULL);
	is_squotes = *src == '\'' && *(src + size - 1) == '\'';
	is_dquotes = *src == '\"' && *(src + size - 1) == '\"';
	if (is_squotes || is_dquotes)
	{
		new = ft_substr(src, 1, size - 2);
		if (new)
			return (new);
	}
	return (NULL);
}
