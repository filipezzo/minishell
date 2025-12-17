#include "minishell.h"

static void parse_and_add(t_shell *shell, char *env_str)
{
    int i;
    char *key;
    char *value;

    i = 0;
    while (env_str[i] && env_str[i] != '=')
        i++;
    if (env_str[i] != '=')
        return;
    key = ft_substr(env_str, 0, i);
    value = ft_strdup(env_str + i + 1);
    if (key && value)
    {
        update_or_create_node(&shell->env_list, key, value);
    }
    if (key)
        free(key);
    if (value)
        free(value);
}

void init_env(t_shell *shell, char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        parse_and_add(shell, envp[i]);
        i++;
    }
}