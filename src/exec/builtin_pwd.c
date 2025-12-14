#include "minishell.h"

int builtin_pwd()
{
    char buffer[PATH_MAX];

    if (getcwd(buffer, PATH_MAX) != NULL)
    {
        ft_putstr_fd(buffer, STDOUT_FILENO);
        write(STDOUT_FILENO, "\n", 1);
        return (0);
    }
    perror("minishell: pwd");
    return (1);
}