/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:49:31 by fsousa            #+#    #+#             */
/*   Updated: 2025/12/15 17:49:32 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int builtin_echo_has_flag(const char *str)
{
    int i;
    if (!str || str[0] != '-' || str[1] != 'n')
        return (0);
    i = 2;
    while (str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}
int builtin_echo(t_cmd *cmd)
{
    int i;
    int newline;
    char **args;

    if (!cmd || !cmd->args || !cmd->args[0])
        return (1);
    i = 1;
    newline = 1;
    args = cmd->args;
    while (args[i] && builtin_echo_has_flag(args[i]))
    {
        newline = 0;
        i++;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if (args[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (newline)
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}