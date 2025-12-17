/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:49:34 by fsousa            #+#    #+#             */
/*   Updated: 2025/12/16 15:47:19 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_env(t_env *list, char **args)
{
	if (!handling_builtin_error_args(args, "env", 2))
		return (127);
	while (list)
	{
		if (list->value)
		{
			ft_putstr_fd(list->key, STDOUT_FILENO);
			write(STDOUT_FILENO, "=", 1);
			ft_putendl_fd(list->value, STDOUT_FILENO);
		}
		list = list->next;
	}
	return (0);
}
