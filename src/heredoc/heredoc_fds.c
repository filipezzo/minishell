#include "minishell.h"

void close_heredoc_fds_cmd(t_cmd *cmd)
{
    t_redir *r;

    if (!cmd)
        return;
    r = cmd->redirections;
    while (r)
    {
        if (r->type == REDIR_HEREDOC && r->heredoc_fd != -1)
        {
            close(r->heredoc_fd);
            r->heredoc_fd = -1;
        }
        r = r->next;
    }
}