/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:13:35 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/08 17:15:26 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(char *src)
{
	size_t	i;
	long	res;
	int		sign;

	sign = 1;
	res = 0;
	i = 0;
	while (src[i] && ft_isspace(src[i]))
		i++;
	if (src[i] == '-' || src[i] == '+')
	{
		if (src[i++] == '-')
			sign *= -1;
		i++;
	}
	while (src[i] && ft_isdigit(src[i]))
	{
		res = 10 * res + (src[i] % 48);
		i++;
	}
	return (res * sign);
}
