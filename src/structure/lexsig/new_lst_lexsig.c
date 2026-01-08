/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lst_lexsig.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:37:33 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/05 14:46:09 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexsig	**new_lst_lexsig(void)
{
	t_lexsig	**signals;
	size_t		size;

	size = 12;
	signals = ft_calloc(size + 1, sizeof(t_lexsig *));
	if (!signals)
		return (NULL);
	signals[0] = new_lexsig(REDIR_APPEND, ">>", 2);
	signals[1] = new_lexsig(REDIR_HEREDOC, "<<", 2);
	signals[2] = new_lexsig(AND, "&&", 2);
	signals[3] = new_lexsig(OR, "||", 2);
	signals[4] = new_lexsig(REDIR_IN, "<", 1);
	signals[5] = new_lexsig(REDIR_OUT, ">", 1);
	signals[6] = new_lexsig(PIPE, "|", 1);
	signals[7] = new_lexsig(LEFT_PAREN, "(", 1);
	signals[8] = new_lexsig(RIGHT_PAREN, ")", 1);
	signals[9] = new_lexsig(BACKGROUND, "&", 1);
	signals[10] = new_lexsig(SEPARATOR, ";", 1);
	signals[11] = NULL;
	return (signals);
}
