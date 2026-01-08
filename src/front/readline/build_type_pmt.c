/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_type_pmt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:03:38 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/26 11:24:37 by mhidani          ###   ########.fr       */
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

	isroot = ft_strncmp(user, "root", 4) == 0 && ft_strncmp(type, "#", 1) == 0;
	isother = ft_strncmp(user, "root", 4) != 0 && ft_strncmp(type, "$", 1) == 0;
	return (isroot || isother);
}
