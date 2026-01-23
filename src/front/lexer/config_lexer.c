/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:47:15 by fsousa            #+#    #+#             */
/*   Updated: 2026/01/23 13:08:56 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lexconfig	*create_sig(t_type type, char *str)
{
	t_lexconfig	*sig;

	sig = malloc(sizeof(t_lexconfig));
	if (!sig)
		return (NULL);
	sig->mstype = LEXSIG_T;
	sig->type = type;
	sig->sign = ft_strdup(str);
	sig->size = ft_strlen(str);
	sig->mstype = LEXSIG_T;
	return (sig);
}

t_lexconfig	**init_lexer_config(void)
{
	t_lexconfig	**sigs;
	size_t		i;

	sigs = ft_calloc(12, sizeof(t_lexconfig *));
	if (!sigs)
		return (NULL);
	i = 0;
	sigs[i++] = create_sig(REDIR_HEREDOC, "<<");
	sigs[i++] = create_sig(REDIR_APPEND, ">>");
	sigs[i++] = create_sig(AND, "&&");
	sigs[i++] = create_sig(OR, "||");
	sigs[i++] = create_sig(PIPE, "|");
	sigs[i++] = create_sig(REDIR_IN, "<");
	sigs[i++] = create_sig(REDIR_OUT, ">");
	sigs[i++] = create_sig(LEFT_PAREN, "(");
	sigs[i++] = create_sig(RIGHT_PAREN, ")");
	sigs[i++] = create_sig(SEPARATOR, ";");
	sigs[i] = NULL;
	return (sigs);
}

void	free_lexer_config(t_lexconfig **sigs)
{
	int	i;

	if (!sigs)
		return ;
	i = 0;
	while (sigs[i])
	{
		free(sigs[i]->sign);
		free(sigs[i]);
		i++;
	}
	free(sigs);
}
