/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parentheses_rule.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 19:54:24 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/28 12:14:54 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_parentheses_rule(t_dlist *tokens)
{
	t_bnode	*pivot;
	t_type	type;
	int		balance;

	balance = 0;
	pivot = tokens->head;
	while (pivot)
	{
		type = ((t_lexunit *)pivot->data)->type;
		if (type == LPAREN)
			balance++;
		else if (type == RPAREN)
			balance--;
		if (balance < 0)
			return (
				syntax_error_message("syntax error near unexpected token `)`")
			);
		pivot = pivot->right;
	}
	if (balance > 0)
		return (
			syntax_error_message("syntax error near unexpected token `(`")
		);
	return (TRUE);
}
