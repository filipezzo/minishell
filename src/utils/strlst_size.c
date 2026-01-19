/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlst_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:53:15 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/16 18:55:38 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	strlst_size(char **list)
{
	size_t	i;

	if (!list)
		return (0);
	i = 0;
	while (list[i])
		i++;
	return (i);
}
