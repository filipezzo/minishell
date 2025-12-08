
#include "minishell.h"

int main(void)
{
    t_cmd cmd;

    char *args[] = {"echo", "-n", "b", "c", NULL};
    cmd.args = args;
    cmd.next = NULL;
    cmd.redirections = NULL;
    cmd.pid = 0;

    builtin_echo(&cmd);
}
