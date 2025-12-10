#include "minishell.h"

void free_env_node(t_env *node)
{
    if (!node)
        return;
    if (node->key)
        free(node->key);
    if (node->value)
        free(node->value);
    free(node);
}

int is_valid_env_key(char *str)
{
    int i;

    i = 0;

    if (!ft_isalpha(str[i]) && str[i] != '_')
        return (0);
    i++;
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

static void append_end_node(t_env **head, char *key, char *value)
{
    t_env *current;
    t_env *node;

    node = malloc(sizeof(t_env));
    if (!node)
        return;
    node->key = ft_strdup(key);
    if (!node->key)
    {
        free(node);
        return;
    }
    if (value)
    {
        node->value = ft_strdup(value);
        if (!node->value)
        {
            free(node->key);
            free(node);
            return;
        }
    }
    else
        node->value = NULL;
    node->next = NULL;
    if (!*head)
    {
        *head = node;
        return;
    }
    current = *head;
    while (current->next != NULL)
        current = current->next;
    current->next = node;
}

void update_or_create_node(t_env **head, char *key, char *value)
{
    t_env *current;

    current = *head;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            if (value)
            {
                if (current->value)
                    free(current->value);
                current->value = ft_strdup(value);
            }
            return;
        }
        current = current->next;
    }
    append_end_node(head, key, value);
}