/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_names_crrdir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:20:53 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/19 11:21:24 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist	*get_names_crrdir(void)
{
	DIR				*dir;
	struct dirent	*entry;
	t_dlist			*names;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	names = ft_new_dlist();
	if (!names)
	{
		closedir(dir);
		return (NULL);
	}
	entry = readdir(dir);
	while (entry)
	{
		ft_add_nd_dlist(names, ft_strdup(entry->d_name), free);
		entry = readdir(dir);
	}
	closedir(dir);
	return (names);
}
