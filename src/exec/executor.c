/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:07:04 by fsousa            #+#    #+#             */
/*   Updated: 2026/01/12 09:32:45 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child_process(t_shell *shell, t_cmd *cmd, int fd_in,
								int end[2])
{
	set_signals_child();
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->next)
	{
		dup2(end[1], STDOUT_FILENO);
		close(end[1]);
		close(end[0]);
	}
	if (apply_redirect(cmd) == 0)
		exit(1);
	if (is_command_builtin(cmd->args[0]))
		exit(run_builtin(shell, cmd));
	else
		execute_external(shell, cmd);
}

static void	wait_all_children(t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		sig;

	pid = 0;
	while (pid != -1 || errno != ECHILD)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == shell->last_pid)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				shell->exit_status = 128 + sig;
				if (sig == SIGINT)
					write(1, "\n", 1);
				else if (sig == SIGQUIT)
					write(1, "Quit (core dumped)\n", 19);
				g_signal_status = shell->exit_status;
			}
		}
	}
}

static pid_t	handle_fork(t_shell *shell, t_cmd *cmd, int fd_in, int end[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
		handle_child_process(shell, cmd, fd_in, end);
	return (pid);
}

static void	execute_pipeline(t_shell *shell, t_cmd *cmd)
{
	int		fd_in;
	int		end[2];
	pid_t	pid;

	set_signals_exec();
	fd_in = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next)
			pipe(end);
		pid = handle_fork(shell, cmd, fd_in, end);
		if (!cmd->next)
			shell->last_pid = pid;
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (cmd->next)
		{
			fd_in = end[0];
			close(end[1]);
		}
		cmd = cmd->next;
	}
	wait_all_children(shell);
}

void	executor(t_shell *shell)
{
	t_cmd	*head;

	head = shell->cmd_list;
	if (!head)
		return ;
	if (!head->next && is_command_builtin(head->args[0]))
	{
		shell->saved_stdin = dup(STDIN_FILENO);
		shell->saved_stdout = dup(STDOUT_FILENO);
		if (apply_redirect(head))
			shell->exit_status = run_builtin(shell, head);
		else
			shell->exit_status = 1;
		dup2(shell->saved_stdin, STDIN_FILENO);
		dup2(shell->saved_stdout, STDOUT_FILENO);
		close(shell->saved_stdin);
		close(shell->saved_stdout);
	}
	else
		execute_pipeline(shell, head);
}
