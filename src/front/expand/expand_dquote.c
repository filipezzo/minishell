/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:13:16 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/19 16:42:15 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_expanded_value(t_shell *sh, char *env);
static void	cleanup_and_next(char *env, char *value, size_t *i, t_bool next);

void	expand_dquote(t_shell *sh, t_cmd *cmd, size_t idx)
{
	char	*aux;
	char	*env;
	char	*value;
	size_t	i;

	i = 0;
	while (cmd->args[idx][i])
	{
		env = find_env(cmd->args[idx], &i);
		if (!env)
			continue ;
		value = get_expanded_value(sh, env);
		if (!value)
		{
			cleanup_and_next(env, NULL, &i, TRUE);
			continue ;
		}
		aux = replace_once(cmd->args[idx], env, value);
		free(cmd->args[idx]);
		cmd->args[idx] = aux;
		cleanup_and_next(env, value, &i, TRUE);
	}
}

static char	*get_expanded_value(t_shell *sh, char *env)
{
	t_bool	check_next;
	char	*next;

	next = (env + 1);
	check_next = (*next != ' ' && *next != '\t' && *next != '\n');
	if (*env == '$' && *next && check_next)
		return (expand_dollar(sh, env));
	else if (*env == '~')
		return (expand_tilde());
	return (NULL);
}

static void	cleanup_and_next(char *env, char *value, size_t *i, t_bool next)
{
	if (env)
		free(env);
	if (value)
		free(value);
	if (next)
		(*i)++;
}
