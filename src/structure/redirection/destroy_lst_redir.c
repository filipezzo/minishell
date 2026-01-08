/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_lst_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:21:51 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/06 00:32:19 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_lst_redir(void *ptr)
{
	t_redir	*redir;

	if (!ptr)
		return ;
	redir = (t_redir *)ptr;
	while (redir)
	{
		destroy_redir(redir);
		redir = redir->next;
	}
}
