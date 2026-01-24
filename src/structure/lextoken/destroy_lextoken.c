/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_lextoken.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:23:45 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/05 20:09:28 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_lextoken(void *ptr)
{
	t_lextoken	*token;

	if (!ptr)
		return ;
	token = (t_lextoken *)ptr;
	if (token->mstype != LEXTOKEN_T)
		return ;
	free(token->content);
	free(token);
}
