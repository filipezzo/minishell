#include "minishell.h"

int builtin_exit(t_shell *shell, char **args)
{
    long number;

    ft_putendl_fd("exit", 2);
    if (!args[1])
    {
        int exit_code = shell->exit_status;
        free_shell(shell);
        exit(exit_code);
    }
    if (!ft_isnumeric(args[1]))
    {
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(args[1], 2);

        ft_putendl_fd(": numeric argument required.", 2);
        free_shell(shell);
        exit(255);
    }
    if (args[2])
    {
        ft_putendl_fd("minishell: exit: too many arguments.", 2);
        return (1);
    }
    number = ft_atol(args[1]);
    free_shell(shell);
    exit(number % 256);
}