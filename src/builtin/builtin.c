/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:49:52 by fsousa            #+#    #+#             */
/*   Updated: 2025/12/16 15:15:56 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_command_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env"))
		return (1);
	return (0);
}

int run_builtin(t_shell *shell, t_cmd *cmd)
{
	int status;

	status = 0;
	if (!shell || !cmd)
		return (1);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		status = builtin_cd(shell, cmd->args);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		status = builtin_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		status = builtin_env(shell->env_list, cmd->args);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		status = builtin_exit(shell, cmd->args);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		status = builtin_export(shell, cmd->args);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		status = builtin_pwd();
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		status = builtin_unset(&shell->env_list, cmd->args);
	return (status);
}
