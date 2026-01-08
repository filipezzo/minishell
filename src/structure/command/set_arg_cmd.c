/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_arg_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:25:40 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/06 00:35:59 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*set_arg_cmd(t_cmd *cmd, char *src)
{
	char	**new_args;
	size_t	i;
	size_t	size;

	if (!cmd || !src)
		return (NULL);
	size = 0;
	while (cmd->args && cmd->args[size])
		size++;
	if (size == 0)
		new_args = ft_calloc(2, sizeof(char *));
	else
		new_args = ft_calloc(size + 2, sizeof(char *));
	if (!new_args)
		return (NULL);
	i = 0;
	while (cmd->args && i < size)
	{
		new_args[i] = ft_strdup(cmd->args[i]);
		i++;
	}
	new_args[size] = ft_strdup(src);
	destroy_string_lst(cmd->args);
	cmd->args = new_args;
	return (cmd);
}
