/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_user_pmt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:18:10 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/26 11:45:33 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_user_pmt(char **crr)
{
	char	*value;

	if (*crr && ft_strncmp(*crr, "unknown", 7) != 0)
		return (*crr);
	else if (*crr && ft_strncmp(*crr, "unknown", 7) == 0)
		free(*crr);
	value = getenv("USER");
	if (value)
	{
		*crr = ft_strdup(value);
		return (*crr);
	}
	else
	{
		*crr = ft_strdup("unknown");
		return (*crr);
	}
}
