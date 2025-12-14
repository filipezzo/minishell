#include "minishell.h"

void free_shell(t_shell *shell)
{
    t_env *temp;
    t_cmd *tmp;

    if (!shell)
        return;

    while (shell->env_list)
    {
        temp = shell->env_list->next;
        free_env_node(shell->env_list);
        shell->env_list = temp;
    }
    while (shell->cmd_list)
    {
        tmp = shell->cmd_list->next;
        free(shell->cmd_list);
        shell->cmd_list = tmp;
    }
    // rl_clear_history();
}