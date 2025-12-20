/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:43:22 by fsousa            #+#    #+#             */
/*   Updated: 2025/12/20 15:43:52 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	lex_isjump(char c)
{
	char	*signs;
	size_t	i;

	if (ft_isspace(c))
		return (TRUE);
	if (c == '\'' || c == '\"')
		return (TRUE);
	signs = "|&;()<>";
	i = 0;
	while (signs[i] && c != signs[i])
		i++;
	if (c == signs[i])
		return (TRUE);
	return (FALSE);
}
