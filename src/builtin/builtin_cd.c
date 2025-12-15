/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:49:09 by fsousa            #+#    #+#             */
/*   Updated: 2025/12/15 17:49:18 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_value(t_env *env, char *key)
{
    if (!env)
        return (NULL);
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

static char *get_target_path(t_env *env, char **args)
{
    if (!args[1])
    {
        char *home;

        home = get_env_value(env, "HOME");
        if (!home)
        {
            ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
            return (NULL);
        }
        return (home);
    }
    else if (ft_strcmp(args[1], "-") == 0)
    {
        char *path;
        path = get_env_value(env, "OLDPWD");
        if (!path)
        {
            ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
            return (NULL);
        }
        ft_putendl_fd(path, 1);
        return (path);
    }
    return (args[1]);
}

int builtin_cd(t_shell *shell, char **args)
{
    char *target;
    char cwd_buffer[PATH_MAX];
    char *old_pwd_copy;

    if (args[1] && args[2])
    {
        ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
        return (1);
    }
    if (getcwd(cwd_buffer, PATH_MAX))
        old_pwd_copy = ft_strdup(cwd_buffer);
    else
        old_pwd_copy = ft_strdup("");
    target = get_target_path(shell->env_list, args);
    if (!target)
    {
        free(old_pwd_copy);
        return (1);
    }
    if (chdir(target) == -1)
    {
        ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
        perror(args[1]);
        free(old_pwd_copy);
        return (1);
    }
    update_or_create_node(&shell->env_list, "OLDPWD", old_pwd_copy);
    free(old_pwd_copy);
    if (getcwd(cwd_buffer, PATH_MAX))
        update_or_create_node(&shell->env_list, "PWD", cwd_buffer);
    return 0;
}