/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_type_pmt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:03:38 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/16 15:19:55 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_unmodifiable(char *user, char *type);

char	*build_type_pmt(char *user, char **crr)
{
	char	*target;

	if (!user || !*crr || (user && ft_strncmp(user, "unknown", 7) == 0))
	{
		free(*crr);
		*crr = ft_strdup("?");
		return (*crr);
	}
	if (is_unmodifiable(user, *crr))
		return (*crr);
	free(*crr);
	target = "$";
	if (ft_strncmp(user, "root", 4) == 0)
		target = "#";
	*crr = ft_strdup(target);
	return (*crr);
}

static t_bool	is_unmodifiable(char *user, char *type)
{
	t_bool	isroot;
	t_bool	isother;
	t_bool	ishash;
	t_bool	isdollar;

	isroot = ft_strncmp(user, "root", 4) == 0;
	ishash = ft_strncmp(type, "#", 1) == 0;
	isdollar = ft_strncmp(type, "$", 1) == 0;
	isother = ft_strncmp(user, "root", 4) != 0;
	return (isroot || isother);
}
