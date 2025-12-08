/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:31:26 by mhidani           #+#    #+#             */
/*   Updated: 2025/07/25 08:38:51 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*res;

	if (!s)
		return (NULL);
	size = ft_strlen((char *)s);
	if (start >= size)
		return (ft_calloc(1, 1));
	if (len > (size - start))
		len = (size - start);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, (char *)(s + start), len + 1);
	return (res);
}
