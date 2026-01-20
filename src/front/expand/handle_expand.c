/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:27:28 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/19 16:21:23 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_ifs(char c);

char	*expand_dollar(t_shell *sh, char *env)
{
	char	*var_name;
	char	*value;

	if (!env || *env != '$')
		return (ft_strdup(""));
	if (env[1] && env[1] == '?')
		return (ft_itoa(sh->exit_status));
	if (env[1] && env[1] == '$')
		return (ft_itoa(getpid()));
	if (ft_isdigit(env[1]))
		return (ft_strdup(""));
	var_name = env + 1;
	value = getenv(var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
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
	size_t	start;

	while (src[*idx] && src[*idx] != '$' && src[*idx] != '~')
		(*idx)++;
	start = *idx;
	if (src[*idx] && src[*idx] == '~')
	{
		(*idx)++;
		while (src[*idx] && !is_ifs(src[*idx]))
			(*idx)++;
		return (ft_substr(src, start, *idx - start));
	}
	if (src[*idx] && src[*idx] == '$')
	{
		(*idx)++;
		if (src[*idx] == '?' || src[*idx] == '$' || ft_isdigit(src[*idx]))
		{
			(*idx)++;
			return (ft_substr(src, start, 2));
		}
		while (src[*idx] && (ft_isalnum(src[*idx]) || src[*idx] == '_'))
			(*idx)++;
		return (ft_substr(src, start, *idx - start));
	}
	return (NULL);
}

static t_bool	is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}
