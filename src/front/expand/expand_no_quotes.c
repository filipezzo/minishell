/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_no_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 21:11:39 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/20 17:45:05 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_expand(t_shell *shell, char *src);
static void	expand_tokens(t_shell *shell, t_dlist *tokens);
static char	*expand_dollar(t_shell *shell, char *src);

void	expand_simple(t_shell *shell, t_cmd *cmd, size_t i)
{
	char	*aux;
	char	**arg;

	if (!shell || !cmd || !cmd->args)
		return ;
	arg = &cmd->args[i];
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
	arg = &cmd->args[i];
	aux = handle_expand(shell, *arg);
	if (aux)
	{
		free(*arg);
		*arg = aux;
	}
}

static char	*handle_expand(t_shell *shell, char *src)
{
	t_dlist	*tokens;
	t_bnode	*node;
	char	*aux;
	char	*res;

	if (!shell || !src)
		return (NULL);
	tokens = ft_new_dlist();
	if (!tokens)
		return (NULL);
	minilexer_expand(tokens, src);
	expand_tokens(shell, tokens);
	res = ft_calloc(1, sizeof(char));
	node = tokens->head;
	while (node)
	{
		aux = ft_strcatt(res, (char *)node->data);
		free(res);
		res = aux;
		node = node->right;
	}
	ft_destroy_dlist(tokens);
	return (res);
}

static void	expand_tokens(t_shell *shell, t_dlist *tokens)
{
	t_bnode	*node;
	char	*aux;

	node = tokens->head;
	while (node)
	{
		if (*(char *)node->data == '$')
		{
			aux = expand_dollar(shell, (char *)node->data);
			if (aux)
			{
				free(node->data);
				node->data = aux;
			}
		}
		node = node->right;
	}
}

static char	*expand_dollar(t_shell *shell, char *src)
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
		return (ft_itoa((int)getpid()));
	if (ft_strnstr(src, "$_", 2))
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
