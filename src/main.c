/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:59:06 by fsousa            #+#    #+#             */
/*   Updated: 2026/01/12 10:11:48 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	t_lexsig	**lexer_conf;
	t_dlist		*tokens;
	t_astree	*tree;
	char		*input;

	(void)argc;
	(void)argv;
	ft_memset(&shell, 0, sizeof(t_shell));
	init_env(&shell, envp);
	init_signals();
	lexer_conf = init_lexer_config();
	while (1)
	{
		if (g_signal_status != 0)
		{
			shell.exit_status = g_signal_status;
			g_signal_status = 0;
		}
		input = readline("minishell$ ");
		if (!input)
		{
			if (g_signal_status == 130)
				continue ;
			printf("exit\n");
			break ;
		}
		if (input[0] != '\0')
		{
			add_history(input);
			tokens = lexer(input, lexer_conf);
			if (syntax_analyze(tokens))
			{
				tree = parser(tokens);
				if (tree && tree->root)
				{
					run_ast(&shell, tree->root);
					init_signals();
				}
				if (tree)
					destroy_astree(tree);
				ft_destroy_dlist(tokens);
			}
		}
		free(input);
	}
	free_lexer_config(lexer_conf);
	free_shell(&shell);
	rl_clear_history();
	return (shell.exit_status);
}
