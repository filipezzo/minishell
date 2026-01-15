/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:27:28 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/15 09:29:30 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_dollar_env(char *src, size_t *idx);

char	*expand_dollar(t_shell *sh, char *env)
{
	char	*value;

	value = NULL;
	if (!env || (env && *env != '$'))
		return (NULL);
	if (*(env + 1) && *(env + 1) == '?')
		return (ft_itoa(sh->exit_status));
	else
	{
		value = getenv((env + 1));
		if (!value)
			return (ft_strdup(""));
		return (ft_strdup(value));
	}
}

char	*expand_tilde(void)
{
	char	*value;
	char	*env;

	env = getenv("HOME");
	if (!env)
		return (NULL);
	value = ft_strdup(env);
	if (!value)
		return (NULL);
	return (value);
}

char	*find_env(char *src, size_t *idx)
{
	if (src[*idx] == '~')
	{
		(*idx)++;
		return (ft_strdup("~"));
	}
	while (src[*idx])
	{
		if (src[*idx] == '$')
			return (get_dollar_env(src, idx));
		(*idx)++;
	}
	return (NULL);
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
	if (src[j] == '?')
		j++;
	env = ft_calloc(j - *idx + 1, sizeof(char));
	if (!env)
		return (NULL);
	ft_strlcpy(env, src + *idx, j - *idx + 1);
	*idx = j;
	return (env);
}
