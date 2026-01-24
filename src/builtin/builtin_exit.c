/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:49:38 by fsousa            #+#    #+#             */
/*   Updated: 2026/01/13 18:14:28 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	verify_exit_args(t_shell *shell, char **args);

int	builtin_exit(t_shell *shell, char **args)
{
	long	number;
	int		exit_code;

	ft_putendl_fd("exit", 2);
	if (!args[1])
	{
		exit_code = shell->exit_status;
		free_shell(shell);
		exit(exit_code);
	}
	verify_exit_args(shell, args);
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments.", 2);
		return (1);
	}
	number = ft_atol(args[1]);
	free_shell(shell);
	exit(number % 256);
}

static void	verify_exit_args(t_shell *shell, char **args)
{
	if (!ft_isnumeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required.", 2);
		free_shell(shell);
		exit(255);
	}
}
