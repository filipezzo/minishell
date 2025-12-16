
#include "minishell.h"

int main(void)
{
    t_shell shell;
	t_cmd cmd_node;

	ft_memset(&shell, 0, sizeof(t_shell));
	ft_memset(&cmd_node, 0, sizeof(t_cmd));

	char *args[] = {"pwd", "oi", NULL };
	cmd_node.args = args;
	cmd_node.next = NULL;
	shell.cmd_list = &cmd_node;
	executor(&shell);
	return 0;
}
