/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:37:56 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/21 20:06:25 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_valid_prompt(t_prompt *prompt);
static char		*alloc_all_prompt(t_prompt *prompt);

char	*build_prompt(void)
{
	t_prompt	prompt;
	char		*res;

	prompt.user = build_prompt_user();
	prompt.host = build_prompt_host();
	prompt.dir = build_prompt_dir();
	prompt.utype = build_prompt_utype();
	if (!is_valid_prompt(&prompt))
	{
		destroy_prompt(&prompt);
		return (ft_strdup("minishell$ "));
	}
	res = alloc_all_prompt(&prompt);
	destroy_prompt(&prompt);
	return (res);
}

static t_bool	is_valid_prompt(t_prompt *prompt)
{
	if (ft_strncmp(prompt->user, "unknown", 7) == 0)
		return (FALSE);
	if (ft_strncmp(prompt->host, "unknown", 7) == 0)
		return (FALSE);
	if (ft_strncmp(prompt->dir, "?", 1) == 0)
		return (FALSE);
	if (ft_strncmp(prompt->utype, "?", 1) == 0)
		return (FALSE);
	return (TRUE);
}

static char	*alloc_all_prompt(t_prompt *prompt)
{
	size_t	user;
	size_t	host;
	size_t	dir;
	size_t	utype;
	char	*res;

	user = ft_strlen(prompt->user);
	host = ft_strlen(prompt->host);
	dir = ft_strlen(prompt->dir);
	utype = ft_strlen(prompt->utype);
	res = ft_calloc(user + host + dir + utype + 4, sizeof(char));
	if (!res)
		return (ft_strdup("minishell$ "));
	ft_memmove(res, prompt->user, user);
	res[user] = '@';
	ft_memmove(res + user + 1, prompt->host, host);
	res[user + host + 1] = ':';
	ft_memmove(res + user + host + 2, prompt->dir, dir);
	ft_memmove(res + user + host + dir + 2, prompt->utype, utype);
	res[user + host + dir + utype + 2] = ' ';
	return (res);
}
