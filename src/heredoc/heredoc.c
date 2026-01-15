/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:19:33 by fsousa            #+#    #+#             */
/*   Updated: 2026/01/15 17:37:43 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_delimiter(const char *line, const char *delimiter)
{
	if (!line || !delimiter)
		return (0);
	return (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0);
}

static void	handle_pid_zero(pid_t pid, int *p, char *delimiter)
{
	char	*line;

	line = NULL;
	if (pid == 0)
	{
		close(p[0]);
		set_signals_heredoc_child();
		while (1)
		{
			line = readline("> ");
			if (!line)
				break ;
			if (is_delimiter(line, delimiter))
			{
				free(line);
				break ;
			}
			write(p[1], line, ft_strlen(line));
			write(p[1], "\n", 1);
			free(line);
		}
		close(p[1]);
		_exit(0);
	}
}

static int	handle_pids(pid_t pid, int *p, char *delimiter)
{
	if (pid == -1)
	{
		perror("fork heredoc");
		close(p[0]);
		close(p[1]);
		return (-1);
	}
	handle_pid_zero(pid, p, delimiter);
	return (0);
}

static int	handle_sigint_status(int status, int *p)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_signal_status = 130;
		close(p[0]);
		return (-1);
	}
	return (0);
}

int	run_heredoc(char *delimiter)
{
	int		p[2];
	pid_t	pid;
	int		status;

	if (pipe(p) == -1)
	{
		perror("pipe heredoc");
		return (-1);
	}
	pid = fork();
	if (handle_pids(pid, p, delimiter) == -1)
		return (-1);
	close(p[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	init_signals();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		g_signal_status = 130;
		close(p[0]);
		return (-1);
	}
	handle_sigint_status(status, p);
	return (p[0]);
}
