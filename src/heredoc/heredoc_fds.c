/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:15:34 by fsousa            #+#    #+#             */
/*   Updated: 2026/01/15 13:15:42 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_heredoc_fds_cmd(t_cmd *cmd)
{
	t_redir	*r;

	if (!cmd)
		return ;
	r = cmd->redirections;
	while (r)
	{
		if (r->type == REDIR_HEREDOC && r->heredoc_fd != -1)
		{
			close(r->heredoc_fd);
			r->heredoc_fd = -1;
		}
		r = r->next;
	}
}
