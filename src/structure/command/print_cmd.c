/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:45:37 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/07 11:24:56 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_cmd_args(t_cmd *cmd, int fd);
static void print_cmd_redirs(t_cmd *cmd, int fd);

void	print_cmd(void *ptr, int fd)
{
	t_cmd	*cmd;
	char	*pid;

	if (!ptr)
		return ;
	cmd = (t_cmd *)ptr;
	if (cmd->mstype != COMMAND_T)
		return ;
	pid = ft_itoa(cmd->pid);
	ft_putstr_fd("COMMAND: { ", fd);
	print_cmd_args(cmd, fd);
	print_cmd_redirs(cmd, fd);
	ft_putstr_fd("pid: ", fd);
	ft_putstr_fd(pid, fd);
	ft_putstr_fd(" }", fd);
	free(pid);
}

static void	print_cmd_args(t_cmd *cmd, int fd)
{
	size_t	i;

	i = 0;
	ft_putstr_fd("args: [ ", fd);
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], fd);
		if (cmd->args[i + 1] != NULL)
			ft_putstr_fd(", ", fd);
		i++;
	}
	ft_putstr_fd(" ], ", fd);
}

static void print_cmd_redirs(t_cmd *cmd, int fd)
{
	t_redir	*redir;
	char	*type;

	redir = cmd->redirections;
	ft_putstr_fd("redirs: [ ", fd);
	while (redir)
	{
		if (redir->type == REDIR_IN)
			type = "REDIR_IN";
		else if (redir->type == REDIR_OUT)
			type = "REDIR_OUT";
		else if (redir->type == REDIR_APPEND)
			type = "REDIR_APPEND";
		else if (redir->type == REDIR_HEREDOC)
			type = "REDIR_HEREDOC";
		ft_putstr_fd("{ type: ", fd);
		ft_putstr_fd(type, fd);
		ft_putstr_fd(", file: ", fd);
		ft_putstr_fd(redir->file, fd);
		ft_putstr_fd(" }", fd);
		if (redir->next != NULL)
			ft_putstr_fd(", ", fd);
		redir = redir->next;
	}
	ft_putstr_fd(" ], ", fd);
}
