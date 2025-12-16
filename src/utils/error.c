/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:45:54 by fsousa            #+#    #+#             */
/*   Updated: 2025/12/16 15:45:57 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handling_builtin_error_args(t_shell *shell, char **args, char *builtin)
{
	if (args[1])
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(builtin, STDERR_FILENO);
		ft_putstr_fd(": too many arguments", STDERR_FILENO);
		return (0);
	}
	return (1);
}