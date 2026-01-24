/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_ifs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:49:41 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/20 15:04:14 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Internal Field Separator (IFS)
t_bool	ft_is_ifs(char *src)
{
	if (!src)
		return (FALSE);
	return (ft_strchr(src, ' ')
		|| ft_strchr(src, '\t')
		|| ft_strchr(src, '\n'));
}
