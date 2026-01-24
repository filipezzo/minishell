/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:02:46 by fsousa            #+#    #+#             */
/*   Updated: 2026/01/13 18:25:56 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_path_with_slash(const char *str);
static char	*search_in_path(char *path_env, char *cmd);

char	*find_command_path(t_shell *shell, char *cmd)
{
	char	*path_env;
	char	*found_path;

	if (!cmd)
		return (NULL);
	if (is_path_with_slash(cmd))
	{
		if (access(cmd, F_OK | X_OK) == 0)
		{
			found_path = ft_strdup(cmd);
			return (found_path);
		}
		return (NULL);
	}
	path_env = get_env_value(shell->env_list, "PATH");
	if (!path_env)
		return (NULL);
	found_path = search_in_path(path_env, cmd);
	return (found_path);
}

static int	is_path_with_slash(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static char	*search_in_path(char *path_env, char *cmd)
{
	int		i;
	char	*temp;
	char	*full_path;
	char	**arr;

	i = 0;
	arr = ft_split(path_env, ':');
	if (!arr)
		return (NULL);
	while (arr[i])
	{
		temp = ft_strjoin(arr[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_full_matrix(arr);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_full_matrix(arr);
	return (NULL);
}
