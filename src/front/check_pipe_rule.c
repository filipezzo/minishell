/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_rule.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 19:51:37 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/28 10:29:50 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	left_expected(t_type type);
static t_bool	right_expected(t_type type);

t_bool	check_pipe_rule(t_dlist *tokens)
{
	t_bnode	*pivot;

	pivot = tokens->head;
	while (pivot)
	{
		if (((t_lexunit *)pivot->data)->type == PIPE)
		{
			if (!pivot->left || !pivot->right)
				return (syntax_error_message("unexpected '|'"));
			if (!left_expected(((t_lexunit *)pivot->left->data)->type))
				return (syntax_error_message("unexpected '|'"));
			if (!right_expected(((t_lexunit *)pivot->right->data)->type))
				return (syntax_error_message("unexpected '|'"));
		}
		pivot = pivot->right;
	}
	return (TRUE);
}

static t_bool	left_expected(t_type type)
{
	return (
		type == WORD
		|| type == LPAREN
	);
}

static t_bool	right_expected(t_type type)
{
	return (
		type == WORD
		|| type == RPAREN
	);
}
