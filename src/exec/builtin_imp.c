#include "minishell.h"
#include <string.h>

static int builtin_echo_has_flag(const char *str)
{
    int i;

    if (!str || str[0] != '-' || str[1] != 'n')
        return (0);
    i = 2;

    while (str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return 1;
}
int builtin_echo(t_cmd *cmd)
{
    int newline;
    int i;
    char **args;

    if (!cmd || !cmd->args || !cmd->args[0])
        return (0);
    args = cmd->args;
    newline = 1;
    i = 1;

    while (args[i] && builtin_echo_has_flag(args[i]))
    {
        newline = 0;
        i++;
    }
    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
    return 1;
}