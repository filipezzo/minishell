/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:49:34 by fsousa            #+#    #+#             */
/*   Updated: 2025/12/15 17:49:35 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_env(t_env *list)
{

    while (list)
    {
        if (list->value)
        {
            ft_putstr_fd(list->key, STDOUT_FILENO);
            write(STDOUT_FILENO, "=", 1);
            ft_putstr_fd(list->value, STDOUT_FILENO);
            write(STDOUT_FILENO, "\n", 1);
        }
        list = list->next;
    }
    return (0);
}