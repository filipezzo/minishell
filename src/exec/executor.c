#include "minishell.h"

void executor(t_cmd *cmd)
{
    if (cmd->next == NULL && is_command_build_in(cmd->args[0])) // unico e builtin
    {
        int stdout;
        int stdin;

        stdout = dup(STDOUT_FILENO);
        stdin = dup(STDIN_FILENO);

        if (cmd->redirection)
            apply_redirect(cmd);
        }
}