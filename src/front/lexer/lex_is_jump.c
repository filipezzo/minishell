/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_is_jump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:43:22 by fsousa            #+#    #+#             */
/*   Updated: 2026/01/23 18:36:08 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	lex_is_jump(char c)
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
