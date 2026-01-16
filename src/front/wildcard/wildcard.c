/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 23:14:44 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/16 15:22:37 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_wildcard(char *src);
static void		navast_to_wildcard(t_dlist *found, t_tnode *cursor);
static void		handle_wildcards_arg(t_dlist *found, t_cmd *cmd, size_t idx);
static t_bool	match(char *name, char *ptn);

void	wildcard(t_shell *sh, t_astree *tree)
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
	navast_to_wildcard(found, tree->root);
	ft_destroy_dlist(found);
	closedir(dir);
}

static void	navast_to_wildcard(t_dlist *found, t_tnode *cursor)
{
	t_cmd	*cmd;
	size_t	i;

	if (!cursor)
		return ;
	if (cursor->type == COMMAND_T)
	{
		cmd = get_cmd(cursor);
		i = 0;
		while (cmd->args[i])
		{
			if (is_wildcard(cmd->args[i]))
				handle_wildcards_arg(found, cmd, i);
			i++;
		}
	}
	navast_to_wildcard(found, cursor->left);
	navast_to_wildcard(found, cursor->right);
}

// add items of 
t_dlist	*addstr_lst(t_dlist *lst, char **strlst, size_t start, size_t end)
{
	while (start < end && strlst[start])
	{
		ft_add_nd_dlist(lst, ft_strdup(strlst[start]), free);
		start++;
	}
}

// Convert double-linked list to string list
char	**dlst_to_strlst(t_dlist *list)
{
	size_t	i;
	t_bnode	*cursor;
	char	**strlst;

	strlst = ft_calloc(list->size + 1, sizeof(char *));
	if (!strlst)
		return (NULL);
	i = 0;
	cursor = list->head;
	while (cursor->right && i < list->size)
	{
		strlst[i] = ft_strdup((char *)cursor->data);
		if (!strlst[i])
		{
			destroy_string_lst(strlst);
			break ;
		}
		cursor = cursor->right;
		i++;
	}
	return (strlst);
}

static char	**join_args(t_dlist *lista, char **args, size_t idx)
{
	t_dlist	*new;
	t_bnode	*cursor;
	size_t	size;
	size_t	i;

	new = ft_new_dlist();
	if (!new)
		return (NULL);
	i = 0;
	while (i < idx)
	{
		ft_add_nd_dlist(new, args[i], free);
		i++;
	}
	cursor = lista->head;
	while (cursor->right)
	{
		ft_add_nd_dlist(new, ft_strdup((char *)cursor->data), free);
		cursor = cursor->right;
	}
	size = size_string_lst(args);
	while (i < size)
	{
		ft_add_nd_dlist(new, ft_strdup(args[i]), free);
		i++;
	}
}

static void		handle_wildcards_arg(t_dlist *found, t_cmd *cmd, size_t idx)
{
	char	**new;
	char	*pattern;
	t_bnode	*cursor;
	t_dlist	*matched;
	size_t	i;

	i = 0;
	pattern = cmd->args[idx];
	matched = build_matched(found, pattern);
	cursor = matched->head;
	while (cursor->right)
	{
		// TODO: capturar todos os elementos de args antes do wildcard

		// TODO: capturar todos os elementos de matched
		// TODO: capturar todos os elementos de args depois do wildcard
		cursor = cursor->right;
		i++; // determina quantidade de elementos dentro de args
	}
	ft_destroy_dlist(matched);
	destroy_string_lst(cmd->args);
	cmd->args = new;
}

t_dlist	*build_matched(t_dlist *found, char *ptn)
{
	t_dlist	*matched;
	t_bnode	*cursor;
	t_bool	ignore;
	char	*name;

	matched = ft_new_dlist();
	if (!matched)
		return (NULL);
	cursor = found->head;
	while (cursor->right)
	{
		name = (char *)cursor->data;
		ignore = *name == '.' && *ptn != '.';
		if (!ignore && match(name, ptn))
			ft_add_nd_dlist(matched, ft_strdup(name), free);
		cursor = cursor->right;
	}
	return (matched);
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
