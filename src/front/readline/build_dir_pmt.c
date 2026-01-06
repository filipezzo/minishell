/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_dir_pmt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:03:36 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/05 22:03:32 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		get_crr_directory(char buffer[], size_t size);
static t_bool	is_unmodifiable(char *home, char *crr, char *dir);

char	*build_dir_pmt(char *home, char **dir)
{
	size_t	home_sz;
	size_t	crr_sz;
	char	crr[PATH_MAX];

	get_crr_directory(crr, PATH_MAX);
	if (*dir && is_unmodifiable(home, crr, *dir))
		return (*dir);
	free(*dir);
	home_sz = ft_strlen(home);
	crr_sz = ft_strlen(crr);
	if (ft_strncmp(crr, home, home_sz) == 0)
	{
		ft_memmove(crr, crr + home_sz, crr_sz - home_sz);
		ft_memset(crr + crr_sz - home_sz, '\0', crr_sz - home_sz);
		*dir = ft_strcat(2, "~", crr);
		return (*dir);
	}
	*dir = ft_strdup(crr);
	return (*dir);
}

static void	get_crr_directory(char buffer[], size_t size)
{
	if (getcwd(buffer, size) == NULL)
	{
		buffer[0] = '?';
		ft_memset(buffer + 1, '\0', size - 1);
	}
}

static t_bool	is_unmodifiable(char *home, char *crr, char *dir)
{
	size_t	home_sz;
	size_t	crr_sz;
	t_bool	is_hm;
	t_bool	is_equals;
	t_bool	is_same;

	home_sz = ft_strlen(home);
	crr_sz = ft_strlen(crr);
	is_hm = ft_strncmp(crr, home, home_sz) == 0 && ft_strncmp(dir, "~", 1) == 0;
	is_equals = ft_strncmp(crr + home_sz, dir + 1, crr_sz - home_sz) == 0;
	is_same = ft_strncmp(crr, dir, crr_sz) == 0;
	if (*dir && is_hm && is_equals)
		return (TRUE);
	if (is_same)
		return (TRUE);
	return (FALSE);
}
