/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_lextoken.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:52:45 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/06 00:31:01 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	next_lextoken(t_bnode **cursor)
{
	if (!(*cursor)->right)
	{
		*cursor = NULL;
		return ;
	}
	(*cursor) = (*cursor)->right;
}
