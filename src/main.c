
#include "minishell.h"

int main(void)
{
    t_shell shell;
    char *args[] = {"unset", "USER", "VAR_OCULTA", "NAOEXISTE", NULL};

    ft_memset(&shell, 0, sizeof(t_shell));
    init_mock_env(&shell);

    printf("\n=== 1. AMBIENTE ANTES DO UNSET ===\n");
    builtin_env(shell.env_list);

    printf("\n>>> Executando: unset USER VAR_OCULTA NAOEXISTE\n");
    builtin_unset(&shell.env_list, args);

    printf("\n=== 2. AMBIENTE DEPOIS DO UNSET ===\n");
    builtin_env(shell.env_list);
    return 0;
}
