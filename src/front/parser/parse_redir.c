/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:28:04 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/06 00:43:29 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tnode	*parse_redir(t_tnode *node, t_bnode **cursor)
{
	t_lextoken	*token;
	t_cmd		*cmd;
	t_redir		*redir;
	t_redir		*redir_cursor;

	token = get_lextoken(*cursor);
	cmd = get_cmd(node);
	redir = new_redir(token->type);
	next_lextoken(cursor);
	token = get_lextoken(*cursor);
	redir->file = ft_strdup(token->content);
	if (!cmd->redirections)
		cmd->redirections = redir;
	else
	{
		redir_cursor = cmd->redirections->next;
		while (redir_cursor)
			redir_cursor = cmd->redirections->next;
		redir_cursor = redir;
	}
	next_lextoken(cursor);
	return (node);
}
