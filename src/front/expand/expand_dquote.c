/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:13:16 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/14 22:37:13 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_once(char *src, char *old, char *new);

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
		if (*env == '$')
			value = expand_dollar(sh, env);
		else if (*env == '~')
			value = expand_tilde();
		else
		{
			free(env);
			continue ;
		}
		if (!value)
		{
			free(env);
			i++;
			continue ;
		}
		aux = replace_once(cmd->args[idx], env, value);
		free(cmd->args[idx]);
		cmd->args[idx] = aux;
		free(env);
		free(value);
		i++;
	}
}

static char	*replace_once(char *src, char *old, char *new)
{
	char	*pos;
	char	*result;
	size_t	len_before;
	size_t	len_old;
	size_t	len_src;

	pos = ft_strnstr(src, old, ft_strlen(src));
	if (!pos)
		return (ft_strdup(src));
	len_before = pos - src;
	len_old = ft_strlen(old);
	len_src = ft_strlen(src);
	result = ft_calloc(len_src - len_old + ft_strlen(new) + 1, sizeof(char));
	if (!result)
		return (NULL);
	ft_memcpy(result, src, len_before);
	ft_memcpy(result + len_before, new, ft_strlen(new));
	ft_memcpy(
		result + len_before + ft_strlen(new), pos + len_old,
		len_src - len_before - len_old + 1);
	return (result);
}
