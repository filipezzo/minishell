#include "minishell.h"

t_bool ft_isnumeric(char *str)
{
    int i;

    i = 0;
    if (!str || !str[0])
        return (FALSE);
    if (str[0] == '+' || str[0] == '-')
        i++;
    if (str[i] == '\0')
        return (FALSE);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (FALSE);
        i++;
    }
    return (TRUE);
}