/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 23:14:44 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/16 19:51:47 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_wildcard(char *src);
static void		handle_wildcards_ast(t_dlist *found, t_tnode *cursor);
static char		**modify_args(t_dlist *found, char **args, size_t i_arg);
static t_bool	match(char *name, char *ptn);

void	wildcard(t_astree *tree)
{
	DIR				*dir;
	struct dirent	*entry;
	t_dlist			*found;

	dir = opendir(".");
	if (!dir)
		return ;
	found = ft_new_dlist();
	entry = readdir(dir);
	while (entry)
	{
		ft_add_nd_dlist(found, ft_strdup(entry->d_name), free);
		entry = readdir(dir);
	}
	closedir(dir);
	handle_wildcards_ast(found, tree->root);
	ft_destroy_dlist(found);
}

static void	handle_wildcards_ast(t_dlist *found, t_tnode *cursor)
{
	t_cmd	*cmd;
	char	**new;
	size_t	i;

	if (!cursor)
		return ;
	if (cursor->type == COMMAND)
	{
		i = 0;
		cmd = get_cmd(cursor);
		while (cmd->args[i])
		{
			if (is_wildcard(cmd->args[i]))
			{
				new = modify_args(found, cmd->args, i);
				destroy_string_lst(cmd->args);
				cmd->args = new;
			}
			i++;
		}
	}
	handle_wildcards_ast(found, cursor->left);
	handle_wildcards_ast(found, cursor->right);
}

static t_bool	is_wildcard(char *src)
{
	size_t	last;
	t_bool	no_simple_quotes;
	t_bool	no_double_quotes;
	t_bool	has_wildcard;

	if (!src)
		return (FALSE);
	last = ft_strlen(src);
	no_simple_quotes = *src != '\"' && *(src + last) != '\"';
	no_double_quotes = *src != '\'' && *(src + last) != '\'';
	has_wildcard = ft_strchr(src, '*') || ft_strchr(src, '?');
	return (no_simple_quotes && no_double_quotes && has_wildcard);
}

static char	**modify_args(t_dlist *found, char **args, size_t i_arg)
{
	t_dlist	*modify;
	t_bnode	*cursor;
	t_bool	ignore;
	char	*name;
	char	*pattern;

	modify = ft_new_dlist();
	pattern = args[i_arg];
	cursor = found->head;
	while (cursor->right)
	{
		name = (char *)cursor->data;
		ignore = (*name == '.' && *pattern != '.');
		if (!ignore && match(name, pattern))
			ft_add_nd_dlist(modify, ft_strdup(name), free);
		cursor = cursor->right;
	}
	return (join_res_wildcard(modify, args, i_arg));
}

static t_bool	match(char *name, char *ptn)
{
	char	*star_ptn;
	char	*star_name;

	star_ptn = NULL;
	star_name = NULL;
	while (*name)
	{
		if (*ptn == *name || *ptn == '?')
		{
			ptn++;
			name++;
		}
		else if (*ptn == '*')
		{
			while (*ptn == '*')
				ptn++;
			star_ptn = ptn;
			star_name = name;
		}
		else if (star_ptn)
		{
			star_name++;
			name = star_name;
			ptn = star_ptn;
		}
		else
			return (FALSE);
	}
	while (*ptn == '*')
		ptn++;
	return (*ptn == '\0');
}
