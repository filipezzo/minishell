/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_lst_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:21:51 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/21 20:25:24 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_lst_redir(void *ptr)
{
	t_redir	*redir;
	t_redir	*next;

	if (!ptr)
		return ;
	redir = (t_redir *)ptr;
	while (redir)
	{
		next = redir->next;
		destroy_redir(redir);
		redir = next;
	}
}
