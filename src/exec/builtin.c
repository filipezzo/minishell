#include "minishell.h"

int is_command_builtin(const char *cmd)
{
    if (!cmd)
        return 0;
    if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env"))
        return 1;
    return 0;
}

int run_builtin(t_cmd *cmd)
{
    char **argv; // {"echo", "testando", "duvida", NULL}
    (void)argv;
    if (!cmd || !cmd->args || !cmd->args[0])
        return (0);
    argv = cmd->args;

    return (0);
}