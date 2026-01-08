/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 12:40:35 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/06 00:42:00 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	can_start_expected(t_type type);
static t_bool	can_end_expected(t_type type);

t_bool	syntax_check_lside(t_dlist *tokens, t_type type)
{
	t_bnode		*pivot;
	t_lextoken	*lexunit;
	char		*err;

	err = "unexpected";
	pivot = tokens->head;
	while (pivot)
	{
		lexunit = ((t_lextoken *)pivot->data);
		if (lexunit->type == type)
		{
			if (!pivot->left)
				return (syntax_err_msg(err, lexunit->content));
			if (!can_end_expected(((t_lextoken *)pivot->left->data)->type))
				return (syntax_err_msg(err, lexunit->content));
			if (pivot->right
				&& !can_start_expected(((t_lextoken *)pivot->right->data)->type))
				return (syntax_err_msg(err, lexunit->content));
		}
		pivot = pivot->right;
	}
	return (TRUE);
}

t_bool	syntax_check_adjacency(t_dlist *tokens, t_type type)
{
	t_bnode		*pivot;
	t_lextoken	*lexunit;
	char		*err;

	err = "unexpected";
	pivot = tokens->head;
	while (pivot)
	{
		lexunit = ((t_lextoken *)pivot->data);
		if (lexunit->type == type)
		{
			if (!pivot->left || !pivot->right)
				return (syntax_err_msg(err, lexunit->content));
			if (!can_end_expected(((t_lextoken *)pivot->left->data)->type))
				return (syntax_err_msg(err, lexunit->content));
			if (!can_start_expected(((t_lextoken *)pivot->right->data)->type))
				return (syntax_err_msg(err, lexunit->content));
		}
		pivot = pivot->right;
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
		type = ((t_lextoken *)pivot->data)->type;
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

static t_bool	can_start_expected(t_type type)
{
	return (
		type == WORD
		|| type == LEFT_PAREN
	);
}

static t_bool	can_end_expected(t_type type)
{
	return (
		type == WORD
		|| type == RIGHT_PAREN
	);
}
