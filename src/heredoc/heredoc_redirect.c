/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:02:59 by fsousa            #+#    #+#             */
/*   Updated: 2026/01/15 12:03:44 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_heredoc(t_redir *r)
{
	if (r->heredoc_fd == -1)
		return (0);
	if (dup2(r->heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 heredoc");
		return (0);
	}
	close(r->heredoc_fd);
	r->heredoc_fd = -1;
	return (1);
}
