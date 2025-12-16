
#include "minishell.h"

int main(void)
{
    char buffer[1024];

    if (!getcwd(buffer, 1024))
        return 1;
    printf("%s\n", buffer);
    char *new_path = "/mnt/c/Users/fastn/OneDrive/42";
    if (chdir(new_path) == -1)
        return 1;
    if (!getcwd(buffer, 1024))
        return 1;
    printf("%s\n", buffer);
}
