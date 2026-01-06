/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:40:12 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/06 00:43:57 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tnode	*parse_scommand(t_astree *tree, t_bnode **cursor);
static t_tnode	*handle_new_tnode(t_astree *tree);
static t_bool	is_redirection(t_type type);

t_tnode	*parse_command(t_astree *tree, t_bnode **cursor)
{
	t_lextoken	*token;

	token = get_lextoken(*cursor);
	if (!token)
		return (NULL);
	if (token->type == LEFT_PAREN)
		return (parse_subshell(tree, cursor));
	return (parse_scommand(tree, cursor));
}

static t_tnode	*parse_scommand(t_astree *tree, t_bnode **cursor)
{
	t_tnode		*node;
	t_lextoken	*token;

	token = get_lextoken(*cursor);
	node = handle_new_tnode(tree);
	if (!node)
		return (NULL);
	while (token)
	{
		if (token->type == WORD)
			set_arg_cmd(get_cmd(node), token->content);
		else if (is_redirection(token->type))
		{
			if (!parse_redir(node, cursor))
				return (NULL);
			token = get_lextoken(*cursor);
			continue ;
		}
		else
			break ;
		next_lextoken(cursor);
		token = get_lextoken(*cursor);
	}
	return (node);
}

static t_tnode	*handle_new_tnode(t_astree *tree)
{
	t_tnode	*node;
	t_cmd	*cmd;

	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	node = new_tnode(tree, cmd);
	if (!node)
		return (NULL);
	node->type = COMMAND;
	node->destroy = destroy_cmd;
	node->print = print_cmd;
	return (node);
}

static t_bool	is_redirection(t_type type)
{
	return (
		type == REDIR_IN
		|| type == REDIR_OUT
		|| type == REDIR_APPEND
		|| type == REDIR_HEREDOC
	);
}
