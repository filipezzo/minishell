/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lextoken.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:22:05 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/13 15:32:15 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	new_lextoken(t_lextoken **new, t_type type, char *content)
{
	if (!content && !*content)
		return (FALSE);
	*new = ft_calloc(1, sizeof(t_lextoken));
	if (!new)
		return (FALSE);
	(*new)->mstype = LEXTOKEN_T;
	(*new)->type = WORD;
	if (type)
		(*new)->type = type;
	(*new)->content = content;
	return (TRUE);
}
