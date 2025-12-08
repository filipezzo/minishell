#include "minishell.h"

int redirect_input(const char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror(filename);
        return (0);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        return (0);
    }
    close(fd);
    return (1);
}

int redirect_output(const char *filename)
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror(filename);
        return (0);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        return (0);
    }
    close(fd);
    return (1);
}

int redirect_append(const char *filename)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        perror(filename);
        return (0);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        return (0);
    }
    close(fd);
    return (1);
}

void apply_redirect(t_cmd *cmd)
{
    t_redir *r = cmd->redirection;

    if (!r)
        return;
    while (r)
    {
        if (r->type == REDIR_IN)
        {
            if (!redirect_input(r->file))
                exit(1);
        }
        else if (r->type == REDIR_OUT)
        {
            if (!redirect_output(r->file))
                exit(1);
        }
        else if (r->type == REDIR_APPEND)
        {
            if (!redirect_append(r->file))
                exit(1);
        }
        r = r->next;
    }
}