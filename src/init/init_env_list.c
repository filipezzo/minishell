/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:27:00 by fsousa            #+#    #+#             */
/*   Updated: 2026/01/13 18:23:21 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_matrix(char **arr, int i);
static char	*create_env_string(char *key, char *value);
static int	handle_transform_list(t_env *env_list, char **arr);

char	**env_list_to_array(t_env *env_list)
{
	int		count;
	char	**arr;

	count = count_list_elements(env_list);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	if (!handle_transform_list(env_list, arr))
		return (NULL);
	return (arr);
}

static void	free_matrix(char **arr, int i)
{
	while (i > 0)
	{
		i--;
		free(arr[i]);
	}
	free(arr);
}

static char	*create_env_string(char *key, char *value)
{
	char	*str;
	size_t	len;

	len = ft_strlen(key) + ft_strlen(value) + 2;
	str = malloc(len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, key, len);
	ft_strlcat(str, "=", len);
	ft_strlcat(str, value, len);
	return (str);
}

static int	handle_transform_list(t_env *env_list, char **arr)
{
	t_env	*current;
	int		i;

	i = 0;
	current = env_list;
	while (current)
	{
		if (current->value)
		{
			arr[i] = create_env_string(current->key, current->value);
			if (!arr[i])
			{
				free_matrix(arr, i);
				return (0);
			}
			i++;
		}
		current = current->next;
	}
	arr[i] = NULL;
	return (1);
}
