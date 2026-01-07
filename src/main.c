/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:48:21 by fsousa            #+#    #+#             */
/*   Updated: 2026/01/07 17:58:16 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{

	t_shell shell;
	t_cmd cmd;
	t_redir redir_node;

	(void)argc;
	(void)argv;

	ft_memset(&shell, 0, sizeof(t_shell));
	init_env(&shell, envp);

	ft_memset(&redir_node, 0, sizeof(t_redir));
	redir_node.file = "teste.txt";
	redir_node.type = REDIR_OUT;
	redir_node.next = NULL;

	char *args[] = {"ls", "-la", NULL};
	ft_memset(&cmd, 0, sizeof(t_cmd));
	cmd.args = args;
	cmd.next = NULL;
	cmd.redirections = &redir_node;

	shell.cmd_list = &cmd;
	start_prompt(&shell); // TODO: check order

	printf("--- INICIANDO EXECUÇÃO: ls -la ---\n");
	executor(&shell);
	printf("--- FIM DA EXECUÇÃO (Exit Status: %d) ---\n", shell.exit_status);
	return 0;
}
