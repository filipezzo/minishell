/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:29:51 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/13 10:06:08 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	size_t	src_size;
	char	*duplicated;

	if (!src || n == 0)
		return (NULL);
	i = 0;
	src_size = ft_strlen((char *)src);
	duplicated = (char *)malloc((src_size + 1) * sizeof(char));
	while (src[i] && i < n)
	{
		duplicated[i] = src[i];
		i++;
	}
	duplicated[i] = '\0';
	return (duplicated);
}
