#include "minishell.h"

static int prepare_cmd_heredocs(t_cmd *cmd)
{
    t_redir *r;

    r = cmd->redirections;
    while (r)
    {
        if (r->type == REDIR_HEREDOC)
        {
            if (r->heredoc_fd != -1)
                close(r->heredoc_fd);

            r->heredoc_fd = run_heredoc(r->file);
            init_signals();

            if (r->heredoc_fd == -1)
                return (0);
        }
        r = r->next;
    }
    return (1);
}

int prepare_pipeline_heredocs(t_cmd *cmd_list)
{
    while (cmd_list)
    {
        if (!prepare_cmd_heredocs(cmd_list))
            return (0);
        cmd_list = cmd_list->next;
    }
    return (1);
}
