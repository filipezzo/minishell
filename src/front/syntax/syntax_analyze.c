/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyze.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 16:47:27 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/03 13:08:27 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	syntax_analyze(t_dlist *tokens)
{
	return (
		syntax_check_balance(tokens, LEFT_PAREN, RIGHT_PAREN)
		&& syntax_check_adjacency(tokens, PIPE)
		&& syntax_check_redir(tokens)
		&& syntax_check_lside(tokens, BACKGROUND)
		&& syntax_check_adjacency(tokens, SEPARATOR)
		&& syntax_check_adjacency(tokens, AND)
		&& syntax_check_adjacency(tokens, OR)
	);
}
