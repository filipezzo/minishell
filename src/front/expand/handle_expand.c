/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:27:28 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/14 13:53:51 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_dollar_env(char *src, char *env, size_t *idx);

char	*expand_dollar(t_shell *sh, char *env)
{
	char	*value;

	value = NULL;
	if (!env || (env && *env != '$'))
		return (NULL);
	if (*(env + 1) == '?')
		return (ft_itoa(sh->exit_status));
	else
	{
		value = getenv((env + 1));
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

char	*find_env(t_shell *sh, char *src, size_t *idx)
{
	char	*env;

	while (src[*idx])
	{
		if (src[*idx] == '$')
		{
			get_dollar_env(src, env, idx);
			return (env);
		}
		else if (src[*idx] == '~')
		{
			*idx++;
			return (ft_strdup("~"));
		}
		*idx++;
	}
	return (NULL);
}

static void	get_dollar_env(char *src, char *env, size_t *idx)
{
	size_t	j;

	if (src[*idx] != '$')
		return (NULL);
	j = idx + 1;
	while (src[j] && (ft_isalnum(src[j]) || src[j] == '_'))
		j++;
	ft_strlcpy(env, (src + *idx), j - *idx - 1);
	*idx = j;
	return (j);
}
