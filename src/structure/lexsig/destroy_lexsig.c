/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_lexsig.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:35:38 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/05 20:06:32 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_lexsig(void *ptr)
{
	t_lexsig	*signal;

	if (!ptr)
		return ;
	signal = (t_lexsig *)ptr;
	if (signal->mstype != LEXSIG_T)
		return ;
	free(signal);
}
