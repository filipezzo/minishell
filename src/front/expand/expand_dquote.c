/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:13:16 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/14 13:51:07 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	join_args(char *src, char *env, t_cmd *cmd, size_t idx);

void	expand_dquote(t_shell *sh, t_cmd *cmd, size_t idx)
{
	char	*src;
	char	*env;
	char	*value;
	size_t	i;

	src = ft_strdup(cmd->args[idx]);
	if (!src)
		return ;
	i = 0;
	while (src[i])
	{
		env = find_env(sh, src, &i);
		if (*env == '$')
			value = expand_dollar(sh, env);
		else if (*env == '~')
			value = expand_tilde();
		else
			return ;
		join_args(value, env, cmd, idx);
		i++;
	}
	free(cmd->args[idx]);
	cmd->args[idx] = src;
}

// TODO: preciso criar uma forma para conseguir alocar o valor encontrado nas 
// environments para trocar com sua posição o valor.
static void	join_args(char *src, char *env, t_cmd *cmd, size_t idx)
{
}
