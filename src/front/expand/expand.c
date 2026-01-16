/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:59:01 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/15 15:55:14 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		expand_dissolution(t_shell *sh, t_tnode *node);
static t_bool	is_simple_expand(char *src);
static t_bool	is_dquote_expand(char *src);

void	expand(t_shell *sh, t_tnode *cursor)
{
	if (!cursor)
		return ;
	expand(sh, cursor->left);
	expand(sh, cursor->right);
	if (cursor && cursor->type == COMMAND)
		expand_dissolution(sh, cursor);
}

static void	expand_dissolution(t_shell *sh, t_tnode *node)
{
	t_cmd	*cmd;
	size_t	i;

	cmd = get_cmd(node);
	if (!cmd)
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (is_simple_expand(cmd->args[i]))
			expand_simple(sh, cmd->args[i], cmd);
		else if (is_dquote_expand(cmd->args[i]))
			expand_dquote(sh, cmd, i);
		i++;
	}
}

static t_bool	is_simple_expand(char *src)
{
	t_bool	check_next;
	char	*next;

	if (!src)
		return (FALSE);
	if (*src == '\"' || *src == '\'')
		return (FALSE);
	if (ft_strchr(src, ' ') || ft_strchr(src, '\t') || ft_strchr(src, '\n'))
		return (FALSE);
	next = (src + 1);
	check_next = *next && (*next != ' ' || *next != '\t' || *next != '\n');
	if ((*src == '$' && check_next) || *src == '~')
		return (TRUE);
	return (FALSE);
}

static t_bool	is_dquote_expand(char *src)
{
	if (!src)
		return (FALSE);
	if (*src != '\"' && *(src + ft_strlen(src) - 1) != '\"')
		return (FALSE);
	if (ft_strchr(src, '$') || ft_strchr(src, '~'))
		return (TRUE);
	return (FALSE);
}
