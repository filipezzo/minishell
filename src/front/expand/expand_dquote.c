/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:13:16 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/14 12:51:53 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	join_args(char *src, char **args, size_t idx);

void	expand_dquote(t_shell *sh, t_cmd *cmd, size_t idx)
{
	char	*src;
	char	*value;
	size_t	i;

	src = ft_strdup(cmd->args[idx]);
	if (!src)
		return ;
	i = 0;
	while (src[i])
	{
		value = find_expand(sh, src, &i);
		i++;
	}
	free(cmd->args[idx]);
	cmd->args[idx] = src;
}

// TODO: preciso criar uma forma para conseguir alocar o valor encontrado nas 
// environments para trocar com sua posição o valor.
static void	join_args(char *src, char **args, size_t idx)
{}
