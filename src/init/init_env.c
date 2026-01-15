/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:26:27 by fsousa            #+#    #+#             */
/*   Updated: 2026/01/15 13:42:14 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_shlvl(t_shell *shell);
static void	parse_and_add(t_shell *shell, char *env_str);
static void	update_shlvl(t_shell *shell);


static void	update_shlvl(t_shell *shell)
{
	char	*val_str;
	char	*new_val;
	int		lvl;

	val_str = get_env_value(shell->env_list, "SHLVL");
	if (!val_str)
		lvl = 1;
	else
		lvl = ft_atoi(val_str) + 1;
	if (lvl < 0)
		lvl = 1;
	new_val = ft_itoa(lvl);
	update_or_create_node(&shell->env_list, "SHLVL", new_val);
	free(new_val);
}

static void	parse_and_add(t_shell *shell, char *env_str)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	if (env_str[i] != '=')
		return ;
	key = ft_substr(env_str, 0, i);
	value = ft_strdup(env_str + i + 1);
	if (key && value)
	{
		update_or_create_node(&shell->env_list, key, value);
	}
	if (key)
		free(key);
	if (value)
		free(value);
}

void	init_env(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		parse_and_add(shell, envp[i]);
		i++;
	}
	update_shlvl(shell);
}
