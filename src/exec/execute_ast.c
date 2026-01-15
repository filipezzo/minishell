/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:01:21 by fsousa            #+#    #+#             */
/*   Updated: 2026/01/15 11:41:23 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*get_cmd_from_node(t_tnode *node)
{
	if (!node || !node->data)
		return (NULL);
	return ((t_cmd *)node->data);
}

static t_cmd	*flatten_pipeline(t_tnode *node)
{
	t_cmd	*left_head;
	t_cmd	*right_head;
	t_cmd	*cursor;

	if (!node)
		return (NULL);
	if (node->type == COMMAND)
	{
		return (get_cmd_from_node(node));
	}
	else if (node->type == PIPE)
	{
		left_head = flatten_pipeline(node->left);
		right_head = flatten_pipeline(node->right);
		if (left_head)
		{
			cursor = left_head;
			while (cursor->next)
				cursor = cursor->next;
			cursor->next = right_head;
			return (left_head);
		}
		return (right_head);
	}
	return (NULL);
}

static int	prepare_pipe(t_shell *shell, t_cmd *cmd_list)
{
	t_cmd	*cursor;
	t_cmd	*next_backup;

	if (!prepare_pipeline_heredocs(cmd_list))
	{
		if (g_signal_status == 130)
			shell->exit_status = 130;
		cursor = cmd_list;
		while (cursor)
		{
			next_backup = cursor->next;
			cursor->next = NULL;
			cursor = next_backup;
		}
		return (0);
	}
	return (1);
}

static void	run_pipeline_node(t_shell *shell, t_tnode *node)
{
	t_cmd	*cmd_list;
	t_cmd	*cursor;
	t_cmd	*next_backup;

	cmd_list = flatten_pipeline(node);
	if (!cmd_list)
		return ;
	if (!prepare_pipe(shell, cmd_list))
		return ;
	shell->cmd_list = cmd_list;
	executor(shell);
	cursor = cmd_list;
	while (cursor)
	{
		next_backup = cursor->next;
		cursor->next = NULL;
		cursor = next_backup;
	}
	shell->cmd_list = NULL;
}

void	run_ast(t_shell *shell, t_tnode *node)
{
	if (!node)
		return ;
	if (node->type == SUBSHELL)
	{
		run_ast(shell, node->left);
		return ;
	}
	if (node->type == AND)
	{
		run_ast(shell, node->left);
		if (shell->exit_status == 0)
			run_ast(shell, node->right);
	}
	else if (node->type == OR)
	{
		run_ast(shell, node->left);
		if (shell->exit_status != 0)
			run_ast(shell, node->right);
	}
	else if (node->type == PIPE || node->type == COMMAND)
	{
		run_pipeline_node(shell, node);
	}
}
