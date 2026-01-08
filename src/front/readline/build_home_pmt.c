/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_home_pmt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:04:31 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/26 11:35:44 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_home_pmt(char **crr)
{
	char	*env;

	if (!*crr || (*crr && ft_strncmp(*crr, "unknown", 7) == 0))
	{
		free(*crr);
		env = getenv("HOME");
		if (env)
		{
			*crr = ft_strdup(env);
			return (*crr);
		}
		else
		{
			*crr = ft_strdup("unknown");
			return (*crr);
		}
	}
	return (*crr);
}
