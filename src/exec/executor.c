/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:07:04 by fsousa            #+#    #+#             */
/*   Updated: 2026/01/15 11:49:22 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
