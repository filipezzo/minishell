
#include "minishell.h"

int main(void)
{
    t_shell shell;

    ft_memset(&shell, 0, sizeof(t_shell));
    init_mock_env(&shell);

    printf("Testando builtin env:\n");
    builtin_env(shell.env_list);
    return 0;
}
