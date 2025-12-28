/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyze.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:47:27 by mhidani           #+#    #+#             */
/*   Updated: 2025/12/28 16:47:30 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	syntax_analyze(t_dlist *tokens)
{
	return (
		syntax_check_balance(tokens, LPAREN, RPAREN)
		&& syntax_check_adjacency(tokens, PIPE)
		&& syntax_check_redir(tokens)
		&& syntax_check_adjacency(tokens, RUN_BKG)
		&& syntax_check_adjacency(tokens, CMD_SEP)
		&& syntax_check_lside(tokens, AND_IF)
		&& syntax_check_adjacency(tokens, AND_OR)
	);
}
