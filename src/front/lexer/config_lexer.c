/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:47:15 by fsousa            #+#    #+#             */
/*   Updated: 2026/01/11 16:01:36 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


static t_lexsig *create_sig(t_type type, char *str)
{
    t_lexsig *sig;

    sig = malloc(sizeof(t_lexsig));
    if (!sig)
        return (NULL);
    sig->type = type;
    sig->sign = ft_strdup(str);
    sig->size = ft_strlen(str);
    sig->mstype = LEXSIG_T;
    return (sig);
}


t_lexsig **init_lexer_config(void)
{
    t_lexsig **sigs;

    sigs = malloc(sizeof(t_lexsig *) * 12); 
    if (!sigs)
        return (NULL);
    int i = 0;
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

void free_lexer_config(t_lexsig **sigs)
{
    int i;
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
