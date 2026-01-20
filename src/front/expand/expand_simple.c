/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:12:39 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/19 17:05:40 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	args_size(char **args);
static size_t	args_pos(char **args, char *ptn);
static void		move_items(char **dst, char **src, size_t stoped, size_t size);
static void		realloc_args_in(t_cmd *cmd, size_t idx, char **splited);

void	expand_simple(t_shell *sh, char *src, t_cmd *cmd)
{
	char	*env;
	char	*value;
	char	*expanded;
	char	**splited;
	size_t	i;
	size_t	pos;

	if (!sh || !src || !cmd)
		return ;
	expanded = ft_strdup(src);
	if (!expanded)
		return ;
	i = 0;
	while (expanded[i])
	{
		env = find_env(expanded, &i);
		if (!env)
			continue ;
		if (*env == '$')
			value = expand_dollar(sh, env);
		else if (*env == '~')
			value = expand_tilde();
		else
		{
			free(env);
			continue ;
		}
		if (!value)
		{
			free(env);
			continue ;
		}
		char *temp = replace_once(expanded, env, value);
		free(expanded);
		expanded = temp;
		free(env);
		free(value);
		i = 0;
	}
	splited = ft_split(expanded, ' ');
	free(expanded);
	if (!splited)
		return ;
	pos = args_pos(cmd->args, src);
	realloc_args_in(cmd, pos, splited);
	destroy_cmtx(splited);
}

static size_t	args_size(char **args)
{
	size_t	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i);
}

static size_t	args_pos(char **args, char *ptn)
{
	size_t	i;

	if (!args || !ptn)
		return (0);
	i = 0;
	while (args[i] && ft_strcmp(args[i], ptn) != 0)
		i++;
	return (i);
}

static void	move_items(char **dst, char **src, size_t stoped, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		dst[stoped + i] = ft_strdup(src[i]);
		i++;
	}
}

static void	realloc_args_in(t_cmd *cmd, size_t idx, char **splited)
{
	size_t	old_size;
	size_t	extra_size;
	char	**new;

	old_size = args_size(cmd->args);
	extra_size = args_size(splited);
	if (extra_size == 1)
	{
		free(cmd->args[idx]);
		cmd->args[idx] = ft_strdup(splited[0]);
		return ;
	}
	new = ft_calloc(old_size + extra_size, sizeof(char *));
	if (!new)
		return ;
	move_items(new, cmd->args, 0, idx);
	move_items(new, splited, idx, extra_size);
	move_items(new, cmd->args + idx + 1, idx + extra_size,
		old_size + extra_size - 1);
	destroy_cmtx(cmd->args);
	cmd->args = new;
}
