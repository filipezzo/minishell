
#include "minishell.h"

int main(void)
{
	t_shell shell;
	t_cmd cmd_node;
	t_env env_list;
	t_env env_list_2;
	t_env env_list_3;
	ft_memset(&shell, 0, sizeof(t_shell));
	ft_memset(&cmd_node, 0, sizeof(t_cmd));
	ft_memset(&env_list, 0, sizeof(t_env));

	char *args[] = {"export", "1TESTE=10", NULL};
	cmd_node.args = args;
	cmd_node.next = NULL;
	shell.cmd_list = &cmd_node;
	env_list.key = ft_strdup("VALUE");
	env_list.value = ft_strdup("a=b+c");
	env_list.next = &env_list_2;

	env_list_2.key = ft_strdup("USER");
	env_list_2.value = ft_strdup("filipe");
	env_list_2.next = &env_list_3;

	env_list_3.key = ft_strdup("PLATAFORM");
	env_list_3.value = ft_strdup("windows");
	env_list_3.next = NULL;

	shell.env_list = &env_list;
	executor(&shell);

	printf("\n\n\nstatus code -> %d\n", shell.exit_status);

	return 0;
}
