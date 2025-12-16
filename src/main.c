
#include "minishell.h"

int main(void)
{
    t_shell shell;
	t_cmd cmd_node;
	t_env env_list;

	ft_memset(&shell, 0, sizeof(t_shell));
	ft_memset(&cmd_node, 0, sizeof(t_cmd));
	ft_memset(&env_list, 0, sizeof(t_env));

	char *args[] = {"env", "lololol", NULL };
	cmd_node.args = args;
	cmd_node.next = NULL;
	shell.cmd_list = &cmd_node;
	env_list.key = ft_strdup("VALUE");
	env_list.value= ft_strdup("a=b+c");
	env_list.next = NULL;
	shell.env_list = &env_list;
	executor(&shell);


	return 0;
}
