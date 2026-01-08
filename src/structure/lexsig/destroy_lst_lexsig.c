/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_lst_lexsig.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:43:21 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/05 14:45:32 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_lst_lexsig(void *ptr)
{
	t_lexsig	**lst;
	size_t		i;

	if (!ptr)
		return ;
	lst = (t_lexsig **)ptr;
	i = 0;
	while (lst[i])
	{
		destroy_lexsig(lst[i]);
		i++;
	}
	free(lst);
}
