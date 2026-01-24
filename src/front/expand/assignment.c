/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:55:34 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/23 17:15:33 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_valid_for_assignment(char *src);
static void		handle_assignment(t_cmd *cmd, size_t idx);
static void		handle_args_assignment(t_cmd *cmd, t_bnode *node, char *new);

void	assignment(t_tnode *node)
{
	size_t	i;
	t_cmd	*cmd;

	if (!node)
		return ;
	if (node->type == COMMAND && node->data)
	{
		i = 0;
		cmd = get_cmd(node);
		while (cmd->args && cmd->args[i])
		{
			if (is_valid_for_assignment(cmd->args[i]))
				handle_assignment(cmd, i);
			i++;
		}
	}
	assignment(node->left);
	assignment(node->right);
}

static t_bool	is_valid_for_assignment(char *src)
{
	size_t	len;

	if (!src)
		return (FALSE);
	len = ft_strlen(src);
	if (src[len - 1] == '=')
		return (TRUE);
	return (FALSE);
}

static void	handle_assignment(t_cmd *cmd, size_t idx)
{
	t_dlist	*args;
	t_bnode	*node;
	char	*new;

	if (!cmd || !cmd->args)
		return ;
	args = convert_cmtx_to_lst(cmd->args);
	if (!args)
		return ;
	node = ft_indexof_dlist(args, idx);
	if (!node->right)
	{
		ft_destroy_dlist(args);
		return ;
	}
	new = ft_strcatt(node->data, node->right->data);
	if (new)
		handle_args_assignment(cmd, node, new);
	ft_destroy_dlist(args);
}

static void	handle_args_assignment(t_cmd *cmd, t_bnode *node, char *new)
{
	t_dlist	*args;

	args = node->structure;
	ft_remove_nd_dlist(args, node->right);
	free(node->data);
	node->data = new;
	destroy_cmtx(cmd->args);
	cmd->args = convert_lst_to_cmtx(args);
}
