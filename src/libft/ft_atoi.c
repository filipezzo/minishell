/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:32:50 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/08 17:16:35 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *src)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
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
