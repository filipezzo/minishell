/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 10:36:42 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/22 13:14:19 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*return_err(char *str, va_list args);

/**
 * Concatenates the number of strings provided into one string.
 * @param elements Number of strings specified that should be concatenated.
 * @param params These are the strings used to compose the final string.
 * @return A string with all the others concatenated.
 */
char	*ft_strcat(size_t elements, char *s1, ...)
{
	va_list	args;
	size_t	i;
	char	*pvtstr;
	char	*aux;
	char	*str;

	if (!s1)
		return (NULL);
	va_start(args, s1);
	i = 0;
	str = ft_strdup(s1);
	pvtstr = va_arg(args, char *);
	while (i < elements - 1 && pvtstr)
	{
		aux = ft_calloc(ft_strlen(str) + ft_strlen(pvtstr) + 1, sizeof(char));
		if (!aux)
			return (return_err(str, args));
		ft_memmove(aux, str, ft_strlen(str));
		ft_memmove(aux + ft_strlen(str), pvtstr, ft_strlen(pvtstr));
		free(str);
		str = aux;
		pvtstr = va_arg(args, char *);
		i++;
	}
	return (va_end(args), str);
}

static char	*return_err(char *str, va_list args)
{
	free(str);
	va_end(args);
	return (NULL);
}
