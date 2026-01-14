/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:45:54 by fsousa            #+#    #+#             */
/*   Updated: 2026/01/13 15:35:19 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handling_builtin_error_args(char **args, char *builtin, int option)
{
	if (args[1] && option == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(builtin, STDERR_FILENO);
		ft_putendl_fd(": too many arguments", STDERR_FILENO);
		return (0);
	}
	if (args[1] && option == 2)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	pms_err(char *msg, int err)
{
	if (!msg || !*msg)
		return (-1);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (err);
}
