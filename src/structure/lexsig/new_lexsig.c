/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexsig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:33:55 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/05 20:06:32 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexsig	*new_lexsig(t_type type, char *sign, size_t size)
{
	t_lexsig	*signal;

	signal = malloc(sizeof(t_lexsig));
	if (!signal)
		return (NULL);
	signal->mstype = LEXSIG_T;
	signal->type = type;
	signal->sign = sign;
	signal->size = size;
	return (signal);
}
