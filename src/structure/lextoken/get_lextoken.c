/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lextoken.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:04:52 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/12 09:18:06 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lextoken	*get_lextoken(void *ptr)
{
	t_bnode		*node;
	t_lextoken	*token;

	if (!ptr)
		return (NULL);
	node = (t_bnode *)ptr;
	if (!node->data)
		return (NULL);
	token = (t_lextoken *)node->data;
	if (token->mstype != LEXTOKEN_T)
		return (NULL);
	return (token);
}

t_lextoken	*bnode_to_lextoken(t_bnode *node)
{
	t_lextoken	*lextoken;

	if (!node)
		return (NULL);
	lextoken = (t_lextoken *)node->data;
	if (lextoken->mstype != LEXTOKEN_T)
		return (NULL);
	return (lextoken);
}
