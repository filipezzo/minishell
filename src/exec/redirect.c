/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:07:07 by fsousa            #+#    #+#             */
/*   Updated: 2025/12/20 15:25:43 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int redirect_heredoc(t_redir *r)
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

static int redirect_input(const char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int redirect_output(const char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int redirect_append(const char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int apply_redirect(t_cmd *cmd)
{
	t_redir *r;

	r = cmd->redirections;
	while (r)
	{
		if (r->type == REDIR_IN)
		{
			if (!redirect_input(r->file))
				return (0);
		}
		else if (r->type == REDIR_OUT)
		{
			if (!redirect_output(r->file))
				return (0);
		}
		else if (r->type == REDIR_APPEND)
		{
			if (!redirect_append(r->file))
				return (0);
		}
		else if (r->type == REDIR_HEREDOC)
		{
			if (!redirect_heredoc(r))
				return 0;
		}
		r = r->next;
	}
	return (1);
}
