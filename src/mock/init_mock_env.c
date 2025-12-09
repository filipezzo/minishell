#include "minishell.h"

static t_env *create_mock_node(char *key, char *value)
{
    t_env *node;

    node = malloc(sizeof(t_env));
    if (!node)
        return NULL;
    if (value)
        node->value = ft_strdup(value);
    else
        node->value = NULL;
    node->key = ft_strdup(key);
    node->next = NULL;
    return node;
}

void init_mock_env(t_shell *shell)
{
    t_env *n1;
    t_env *n2;
    t_env *n3;
    t_env *n4;

    n1 = create_mock_node("USER", "student_42");
    n2 = create_mock_node("PATH", "/usr/local/bin:/usr/bin");
    n3 = create_mock_node("VAR_OCULTA", NULL);
    n4 = create_mock_node("HOME", "/home/filipe");
    shell->env_list = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = NULL;
}