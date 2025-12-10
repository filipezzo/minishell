#include "minishell.h"

int count_list_elements(t_env *list)
{
    int count;

    count = 0;
    while (list)
    {
        count++;
        list = list->next;
    }

    return (count);
}