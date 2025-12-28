/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection_rule.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 19:52:19 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/28 09:54:25 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_redirection(t_type type);
static t_bool	has_target(t_type type);

t_bool	check_redirection_rule(t_dlist *tokens)
{
	t_bnode	*pivot;
	t_type	type;

	pivot = tokens->head;
	while (pivot)
	{
		type = ((t_lexunit *)(pivot->data))->type;
		if (is_redirection(type))
		{
			if (!pivot->right)
				return (
					syntax_error_message("unexpected newline")
				);
			if (!has_target(((t_lexunit *)pivot->right->data)->type))
				return (
					syntax_error_message("unexpected token after redirection")
				);
		}
		pivot = pivot->right;
	}
	return (TRUE);
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

static t_bool	has_target(t_type type)
{
	return (type == WORD);
}
