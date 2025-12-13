#include "minishell.h"

void free_shell(t_shell *shell)
{
    t_env *temp;
    if (!shell)
        return;

    while (shell->env_list)
    {
        temp = shell->env_list->next;
        free_env_node(shell->env_list);
        shell->env_list = temp;
    }
    rl_clear_history();
}