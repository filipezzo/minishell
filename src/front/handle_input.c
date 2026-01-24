/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:24:08 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/23 17:43:31 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_astree	*handle_input(t_shell *shell, char *input)
{
	t_dlist		*tokens;
	t_astree	*astree;

	astree = NULL;
	tokens = lexer(input, shell->lexconfig);
	if (syntax_analyze(tokens))
	{
		astree = parser(tokens);
		expand(shell, astree);
		wildcard(astree);
		sanitize_quotes(astree);
		assignment(astree->root);
	}
	ft_destroy_dlist(tokens);
	return (astree);
}
