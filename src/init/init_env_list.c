#include "minishell.h"

static void free_matrix(char **arr, int i)
{
    while (i > 0)
    {
        i--;
        free(arr[i]);
    }
    free(arr);
}

static char *create_env_string(char *key, char *value)
{
    char *str;
    size_t len;

    len = ft_strlen(key) + ft_strlen(value) + 2;
    str = malloc(len);
    if (!str)
        return NULL;
    ft_strlcpy(str, key, len);
    ft_strlcat(str, "=", len);
    ft_strlcat(str, value, len);
    return (str);
}

char **env_list_to_array(t_env *env_list)
{
    int count;
    char **arr;
    int i;
    t_env *current;

    if (!env_list)
        return (NULL);
    count = count_list_elements(env_list);
    arr = malloc(sizeof(char *) * (count + 1));
    if (!arr)
        return (NULL);
    i = 0;
    current = env_list;
    while (current)
    {
        if (current->value)
        {
            arr[i] = create_env_string(current->key, current->value);
            if (!arr[i])
            {
                free_matrix(arr, i);
                return (NULL);
            }
            i++;
        }
        current = current->next;
    }
    arr[i] = NULL;
    return (arr);
}