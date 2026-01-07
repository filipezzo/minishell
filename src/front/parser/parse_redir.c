/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:28:04 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/07 13:49:05 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	handle_redir_file(t_redir *redir, t_bnode **cursor);

t_tnode	*parse_redir(t_tnode *node, t_bnode **cursor)
{
	t_lextoken	*token;
	t_cmd		*cmd;
	t_redir		*redir;
	t_redir		*redir_cursor;

	token = get_lextoken(*cursor);
	cmd = get_cmd(node);
	redir = new_redir(token->type);
	if (!redir)
		return (NULL);
	if (!handle_redir_file(redir, cursor))
		return (NULL);
	if (!cmd->redirections)
		cmd->redirections = redir;
	else
	{
		redir_cursor = cmd->redirections;
		while (redir_cursor->next)
			redir_cursor = redir_cursor->next;
		redir_cursor->next = redir;
	}
	next_lextoken(cursor);
	return (node);
}

static t_bool	handle_redir_file(t_redir *redir, t_bnode **cursor)
{
	t_lextoken	*token;

	next_lextoken(cursor);
	token = get_lextoken(*cursor);
	if (!token || token->type != WORD)
	{
		destroy_redir(redir);
		return (FALSE);
	}
	redir->file = ft_strdup(token->content);
	if (!redir->file)
	{
		destroy_redir(redir);
		return (FALSE);
	}
	return (TRUE);
}
