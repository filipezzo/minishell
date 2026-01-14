/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:27:28 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/14 12:39:55 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_dollar_env(char *src, size_t *idx);

char	*find_expand(t_shell *sh, char *src, size_t *idx)
{
	char	*env;
	char	*value;
	size_t	j;

	while (src[*idx])
	{
		if (src[*idx] == '$')
		{
			env = get_dollar_env(src, idx);
			value = expand_dollar(sh, env);
			free(env);
			return (value);
		}
		else if (src[*idx] == '~')
		{
			value = getenv("HOME");
			*idx++;
			return (ft_strdup(value));
		}
		*idx++;
	}
	return (NULL);
}

char	*expand_dolar(t_shell *sh, char *src)
{
	char	*value;
	char	*env;

	value = NULL;
	if (!src || (src && *src != '$'))
		return (NULL);
	if (*(src + 1) == '?')
		value = ft_itoa(sh->exit_status);
	else
	{
		env = getenv((src + 1));
		if (!env)
			return (NULL);
		value = ft_strdup(env);
	}
	return (value);
}

char	*expand_tilde(char *src)
{
	char	*value;
	char	*env;

	value = NULL;
	if (!src || (src && *src != '~'))
		return (NULL);
	env = getenv("HOME");
	if (!env)
		return (NULL);
	value = ft_strdup(env);
	if (!value)
		return (NULL);
	return (value);
}

static char	*get_dollar_env(char *src, size_t *idx)
{
	size_t	j;
	char	*env;

	if (src[*idx] != '$')
		return (NULL);
	j = *idx + 1;
	while (src[j] && (ft_isalnum(src[j]) || src[j] == '_'))
		j++;
	ft_strlcpy(env, (src + *idx), j - *idx - 1);
	*idx = j;
	return (env);
}
