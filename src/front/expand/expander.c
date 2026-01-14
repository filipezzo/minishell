/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:27:28 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/13 17:57:32 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
