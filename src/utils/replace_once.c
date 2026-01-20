/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_once.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:41:17 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/19 16:41:33 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_once(char *src, char *old, char *new)
{
	char	*pos;
	char	*result;
	size_t	len_before;
	size_t	len_old;
	size_t	len_src;

	pos = ft_strnstr(src, old, ft_strlen(src));
	if (!pos)
		return (ft_strdup(src));
	len_before = pos - src;
	len_old = ft_strlen(old);
	len_src = ft_strlen(src);
	result = ft_calloc(len_src - len_old + ft_strlen(new) + 1, sizeof(char));
	if (!result)
		return (NULL);
	ft_memcpy(result, src, len_before);
	ft_memcpy(result + len_before, new, ft_strlen(new));
	ft_memcpy(
		result + len_before + ft_strlen(new), pos + len_old,
		len_src - len_before - len_old + 1);
	return (result);
}
