
#include "minishell.h"

int main(int argc, char **argv, char **envp)
{

	t_shell shell;
	t_cmd cmd_node;

	(void)argc;
	(void)argv;

	ft_memset(&shell, 0, sizeof(t_shell));
	init_env(&shell, envp);

	char *args[] = {"env", NULL};
	ft_memset(&cmd_node, 0, sizeof(t_cmd));
	cmd_node.args = args;
	cmd_node.next = NULL;
	shell.cmd_list = &cmd_node;

	executor(&shell);
	return 0;
}
