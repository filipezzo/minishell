/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:27:31 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/12 09:58:14 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_unknown(char *target, char **list, size_t size);

char	*build_prompt(t_prompt *prompt)
{
	char	*user;
	char	*host;
	char	*home;
	char	*dir;
	char	*type;

	if (!prompt)
	{
		prompt = malloc(sizeof(t_prompt));
		if (!prompt)
			return ("minishell$ ");
	}
	user = build_user_pmt(&prompt->user);
	host = build_host_pmt(&prompt->host);
	home = build_home_pmt(&prompt->home);
	dir = build_dir_pmt(prompt->home, &prompt->dir);
	type = build_type_pmt(prompt->user, &prompt->type);
	if (is_unknown("unknown", (char *[]){user, host, home}, 3))
		return (ft_strdup("minishell$ "));
	else if (is_unknown("?", (char *[]){dir, type}, 2))
		return (ft_strdup("minishell$ "));
	free(prompt->display);
	prompt->display = ft_strcat(7, user, "@", host, ":", dir, type, " ");
	return (prompt->display);
}

static t_bool	is_unknown(char *target, char **list, size_t size)
{
	size_t	target_sz;
	size_t	i;

	target_sz = ft_strlen(target);
	i = 0;
	while (i < size)
	{
		if (ft_strncmp(list[i], target, target_sz) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
