/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_string_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 11:54:23 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/16 11:55:37 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	size_string_lst(char **list)
{
	size_t	size;

	if (!list)
		return (0);
	size = 0;
	while (list[size])
		size++;
	return (size);
}
