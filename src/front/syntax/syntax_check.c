/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 12:40:35 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/15 16:15:49 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	end_side(t_type type);
static t_bool	start_side(t_type type);

t_bool	syntax_check_lside(t_dlist *tokens, t_type type)
{
	t_bnode		*pivot;
	t_bnode		*left;
	t_bnode		*right;
	t_lextoken	*lexunit;
	char		*err;

	err = "unexpected";
	pivot = tokens->head;
	while (pivot)
	{
		left = pivot->left;
		right = pivot->right;
		lexunit = ((t_lextoken *)pivot->data);
		if (lexunit->type == type)
		{
			if (!left)
				return (syntax_err_msg(err, lexunit->content));
			if (!start_side(to_lextoken(left)->type))
				return (syntax_err_msg(err, lexunit->content));
			if (right && !end_side(to_lextoken(right)->type))
				return (syntax_err_msg(err, lexunit->content));
		}
		pivot = right;
	}
	return (TRUE);
}

// TODO: check simple command PIPE
t_bool	syntax_check_adjacency(t_dlist *tokens, t_type type)
{
	t_bnode		*pivot;
	t_bnode		*left;
	t_bnode		*right;
	t_lextoken	*lexunit;
	char		*err;

	err = "syntax error near unexpected token";
	pivot = tokens->head;
	while (pivot)
	{
		left = pivot->left;
		right = pivot->right;
		lexunit = (t_lextoken *)pivot->data;
		if (lexunit->type == type)
		{
			if (!left || !right)
				return (syntax_err_msg(err, lexunit->content));
			if (!start_side(to_lextoken(left)->type))
				return (syntax_err_msg(err, lexunit->content));
			if (!end_side(to_lextoken(right)->type))
				return (syntax_err_msg(err, lexunit->content));
		}
		pivot = right;
	}
	return (TRUE);
}

t_bool	syntax_check_balance(t_dlist *tokens, t_type left, t_type right)
{
	t_bnode	*pivot;
	t_type	type;
	char	*err;
	int		balance;

	err = "syntax error near unexpected token";
	balance = 0;
	pivot = tokens->head;
	while (pivot)
	{
		type = to_lextoken(pivot)->type;
		if (type == left)
			balance++;
		else if (type == right)
			balance--;
		if (balance < 0)
			return (syntax_err_msg(err, ")"));
		pivot = pivot->right;
	}
	if (balance > 0)
		return (syntax_err_msg(err, "("));
	return (TRUE);
}

static t_bool	start_side(t_type type)
{
	return (
		type == WORD
		|| type == RIGHT_PAREN
	);
}

static t_bool	end_side(t_type type)
{
	return (
		type == WORD
		|| type == LEFT_PAREN
		|| type == REDIR_IN
		|| type == REDIR_OUT
		|| type == REDIR_APPEND
		|| type == REDIR_HEREDOC
	);
}
