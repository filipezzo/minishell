/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_no_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 21:11:39 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/20 01:36:17 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_simple(t_shell *shell, t_cmd *cmd, size_t i)
{
	char	*aux;
	char	**arg;

	if (!shell || !cmd || !cmd->args)
		return ;
	*arg = (cmd->args + i);
	if (*arg && **arg == '~' && ft_strlen(*arg) == 1)
	{
		free(*arg);
		*arg = ft_strdup(getenv("HOME"));
		return ;
	}
	aux = handle_expand(shell, *arg);
	if (aux)
	{
		free(*arg);
		*arg = aux;
	}
}

void	expand_dquotes(t_shell *shell, t_cmd *cmd, size_t i)
{
	char	*aux;
	char	**arg;

	if (!shell || !cmd || !cmd->args)
		return ;
	*arg = (cmd->args + i);
	aux = handle_expand(shell, *arg);
	if (aux)
	{
		free(*arg);
		*arg = aux;
	}
}

char	*handle_expand(t_shell *shell, char *src)
{
	t_dlist	*tokens;
	char	*res;

	if (!shell || !src)
		return (NULL);
	tokens = ft_new_dlist();
	if (!tokens)
		return (NULL);
	// TODO: criar um mini-lexer.
	// TODO: depois de trabalhar com o source para construir uma lista de tokens
	// separados polos IFS(Internal Field Separator) e depois juntar em uma
	// única string.
	// TODO: strcat de todos os elementos dos tokens, como resultado.
	return (res);
}

void	minilexer_expand(t_dlist *tokens, char *src)
{
	char	*pvt;

	if (*src)
		return ;
	if (*src != '$')
		minilexer_expand(tokens, src + 1);
	pvt = src;
	while (*pvt && *pvt != ' ' && *pvt != '\t' && *pvt != '\n')
	{
		if (*pvt == '?' || *pvt == '$' || *pvt == '_' || ft_isdigit(*pvt))
			ft_add_nd_dlist(tokens, , free);
		pvt++;
	}
}

void	expand_tokens(t_shell *shell, t_dlist *tokens)
{
	t_bnode	*node;
	char	*aux;
	char	**data;

	node = tokens->head;
	while (node)
	{
		*data = (char *)node->data;
		if (**data == '$')
		{
			aux = expand_dollar(shell, *data);
			if (aux)
			{
				free(*data);
				*data = aux;
			}
		}
		node = node->right;
	}
}

// TODO: Handle Expansor ($)
char	*expand_dollar(t_shell *shell, char *src)
{
	char	*env;
	size_t	size;

	if (!src)
		return (NULL);
	size = ft_strlen(src);
	if (*src != '$')
		return (src);
	if (ft_strnstr(src, "$?", 2))
		return (ft_itoa(shell->exit_status));
	if (ft_strnstr(src, "$$", 2))
		return (ft_strdup(getpid()));
	if (ft_strnstr(src, "$_", 2));
		return (ft_strdup(""));
	if (size == 2 && src[1] == '0')
		return (ft_strdup("minishell"));
	if (size == 2 && ft_isdigit(src[1]))
		return (ft_strdup(""));
	env = ft_strdup(getenv(src + 1));
	if (!env)
		return (ft_strdup(""));
	return (env);
}
