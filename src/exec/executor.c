#include "minishell.h"

void executor(t_shell *shell) // ls -la > saida.txt | grep "minishell"
{
    t_cmd *head_cmd;

    head_cmd = shell->cmd_list;

    if (!head_cmd)
        return;

    if (!head_cmd->next && is_command_builtin(head_cmd->args[0]))
    {
        shell->saved_stdin = dup(STDIN_FILENO);
        shell->saved_stdout = dup(STDOUT_FILENO);
        if (apply_redirect(head_cmd))
            run_builtin(shell, head_cmd);
        else
            shell->exit_status = 1;
        dup2(shell->saved_stdin, STDIN_FILENO);
        dup2(shell->saved_stdout, STDOUT_FILENO);
        close(shell->saved_stdin);
        close(shell->saved_stdout);
    }
    else
    {
        // EXECUTE_PIPELINE(SHELL);
    }
}