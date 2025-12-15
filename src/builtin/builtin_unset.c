/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:49:49 by fsousa            #+#    #+#             */
/*   Updated: 2025/12/15 17:49:50 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void remove_node(t_env **head, char *key)
{
    t_env *current;
    t_env *prev;

    if (!head || !*head)
        return;
    if (ft_strcmp((*head)->key, key) == 0)
    {
        current = *head;
        *head = (*head)->next;
        free_env_node(current);
        return;
    }

    prev = *head;
    current = (*head)->next;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            prev->next = current->next;
            free_env_node(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int builtin_unset(t_env **env_list, char **args)
{
    int i;

    i = 1;
    while (args[i])
    {
        remove_node(env_list, args[i]);
        i++;
    }
    return (0);
}