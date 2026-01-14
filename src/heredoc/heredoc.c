
#include "minishell.h"

static int is_delimiter(const char *line, const char *delimiter)
{
    if (!line || !delimiter)
        return 0;
    return (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0);
}

int run_heredoc(char *delimiter)
{
    int p[2];
    char *line;

    if (pipe(p) == -1)
    {
        perror("pipe heredoc");
        return (-1);
    }

    g_signal_status = 0;
    set_signals_heredoc();

    while (1)
    {
        line = readline("> ");

        if (g_signal_status == 130)
        {
            if (line)
                free(line);
            close(p[0]);
            close(p[1]);
            return (-1);
        }

        if (!line)
            break;
        if (is_delimiter(line, delimiter))
        {
            free(line);
            break;
        }
        write(p[1], line, ft_strlen(line));
        write(p[1], "\n", 1);
        free(line);
    }

    close(p[1]);
    return (p[0]);
}
