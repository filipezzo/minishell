/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:20:07 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/05 15:21:30 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_redir(void *ptr)
{
	t_redir	*redir;

	if (!ptr)
		return ;
	redir = (t_redir *)ptr;
	if (redir->mstype != REDIRECTION_T)
		return ;
	free(redir->file);
	free(redir);
}
