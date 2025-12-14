#include "minishell.h"

static void handle_export_arg(t_shell *shell, char *arg)
{
    char *equal_pos;
    char *key;
    char *value;

    equal_pos = ft_strchr(arg, '=');
    if (equal_pos)
    {
        key = ft_substr(arg, 0, equal_pos - arg);
        value = ft_strdup(equal_pos + 1);
    }
    else
    {
        key = ft_strdup(arg);
        value = NULL;
    }
    update_or_create_node(&shell->env_list, key, value);
    free(key);
    if (value)
        free(value);
}

static void sort_env_array(t_env **arr, int size)
{
    int i;
    int j;
    t_env *temp;

    i = 0;
    while (i < size - 1)
    {
        j = 0;
        while (j < size - i - 1)
        {
            if (ft_strcmp(arr[j]->key, arr[j + 1]->key) > 0)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}

static void print_env(t_env **arr, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        ft_putstr_fd("declare -x ", STDOUT_FILENO);
        ft_putstr_fd(arr[i]->key, STDOUT_FILENO);
        if (arr[i]->value)
        {
            ft_putstr_fd("=\"", STDOUT_FILENO);
            ft_putstr_fd(arr[i]->value, STDOUT_FILENO);
            ft_putstr_fd("\"", STDOUT_FILENO);
        }
        write(STDOUT_FILENO, "\n", 1);
        i++;
    }
}

static void print_sorted_env(t_env *list)
{
    int count;
    int i;
    t_env **arr;
    t_env *current;

    count = count_list_elements(list);
    arr = malloc(sizeof(t_env *) * count);
    if (!arr)
        return;
    current = list;
    i = 0;
    while (current)
    {
        arr[i++] = current;
        current = current->next;
    }
    sort_env_array(arr, count);
    print_env(arr, count);
    free(arr);
}

int builtin_export(t_shell *shell, char **args)
{
    int i;
    int exit_code;

    i = 1;
    exit_code = 0;
    if (!args[i])
    {
        print_sorted_env(shell->env_list);
        return (0);
    }
    while (args[i])
    {
        if (!is_valid_env_key(args[i]))
        {
            ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(args[i], 2);
            ft_putendl_fd("': not a valid identifier", 2);
            exit_code = 1;
        }
        else
            handle_export_arg(shell, args[i]);
        i++;
    }
    return (exit_code);
}