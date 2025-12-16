/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:49:45 by fsousa            #+#    #+#             */
/*   Updated: 2025/12/16 15:18:15 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **args)
{
	char	buffer[PATH_MAX];

	if (args[1])
	{
		ft_putendl_fd("minishell: pwd: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (getcwd(buffer, PATH_MAX) != NULL)
	{
		ft_putstr_fd(buffer, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	perror("minishell: pwd");
	return (0);
}
