/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:48:15 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/20 18:02:55 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sanitize_quotes(t_tnode *node)
{
	size_t	i;
	t_cmd	*cmd;
	char	*aux;

	if (!node)
		return ;
	if (node->type == COMMAND)
	{
		i = 0;
		cmd = get_cmd(node);
		while (cmd->args[i])
		{
			if (is_quotes(cmd->args[i]))
			{
				aux = sanitize(cmd);
				free(cmd->args[i]);
				cmd->args[i] = aux;
			}
			i++;
		}
	}
	sanitize_quotes(node->left);
	sanitize_quotes(node->right);
}
