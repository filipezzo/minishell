/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:48:15 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/24 11:11:50 by mhidani          ###   ########.fr       */
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
	char	*new;

	if (!src)
		return (NULL);
	size = ft_strlen(src);
	if (size < 2)
		return (NULL);
	if ((*src == '\'' && *(src + size - 1) == '\'')
		|| (*src == '\"' && *(src + size - 1) == '\"'))
	{
		new = ft_substr(src, 1, size - 2);
		if (new)
			return (new);
	}
	return (NULL);
}
