
#include "minishell.h"

int main(void)
{
    t_shell shell;
    char *args[] = {"USER=FILIPE", NULL};
    ft_memset(&shell, 0, sizeof(t_shell));
    init_mock_env(&shell);

    printf("\n=== 1. AMBIENTE ANTES DO UNSET ===\n");
    builtin_env(shell.env_list);
    builtin_export(&shell, args);

    return 0;
}
