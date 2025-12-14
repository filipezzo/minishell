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