/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrp_strdup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:13:33 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/19 11:14:35 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_wrp_strdup(void *src)
{
	char	*str;

	if (!src)
		return (NULL);
	str = ft_strdup((char *)src);
	return (str);
}
