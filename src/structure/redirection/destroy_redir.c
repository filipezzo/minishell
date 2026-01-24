/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:20:07 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/15 13:52:20 by fsousa           ###   ########.fr       */
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
	if (redir->heredoc_fd != -1)
		close(redir->heredoc_fd);
	free(redir->file);
	free(redir);
}
