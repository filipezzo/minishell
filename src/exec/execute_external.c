#include "minishell.h"

void execute_external(t_shell *shell, t_cmd *cmd)
{
    char **envp;
    char *path;

    path = find_command_path(shell, cmd->args[0]);
    envp = env_list_to_array(shell->env_list);
    if (!path)
    {
        free_full_matrix(envp);
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd->args[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        exit(127);
    }
    execve(path, cmd->args, envp);
    perror("minishell");
    free(path);
    free_full_matrix(envp);
    exit(126);
}