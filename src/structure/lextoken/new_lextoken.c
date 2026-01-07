/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lextoken.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:22:05 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/07 11:56:37 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	new_lextoken(t_lextoken **new, t_type type, char *content)
{
	*new = ft_calloc(1, sizeof(t_lextoken));
	if (!new)
		return (FALSE);
	(*new)->mstype = LEXTOKEN_T;
	(*new)->type = WORD;
	if (type)
		(*new)->type = type;
	content = NULL;
	if (content)
		(*new)->content = content;
	return (TRUE);
}
