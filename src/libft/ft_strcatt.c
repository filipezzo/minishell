/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcatt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:22:29 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/20 15:27:32 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcatt(char *s1, char *s2)
{
	char	*new;
	size_t	s1_size;
	size_t	s2_size;

	if (!s1 || !s2)
		return (NULL);
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	new = ft_calloc(s1_size + s2_size + 1, sizeof(char));
	if (!new)
		return (NULL);
	ft_memmove(new, s1, s1_size);
	ft_memmove(new + s1_size, s2, s2_size);
	new[s1_size + s2_size] = '\0';
	return (new);
}
