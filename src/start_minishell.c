/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:27:38 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/23 17:45:56 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		check_signal(t_shell *shell);
static t_bool	input_valid(char *input);

void	start_minishell(t_shell *shell, char **envp)
{
	char		*prompt;
	char		*input;
	t_astree	*astree;

	init_shell(shell, envp);
	while (TRUE)
	{
		prompt = build_prompt();
		input = readline(prompt);
		free(prompt);
		check_signal(shell);
		if (!input_valid(input))
			break ;
		astree = handle_input(shell, input);
		add_history(input);
		free(input);
		if (astree)
		{
			run_ast(shell, astree->root);
			init_signals();
		}
		destroy_astree(astree);
	}
	free_shell(shell);
}

static void	check_signal(t_shell *shell)
{
	if (g_signal_status != 0)
	{
		shell->exit_status = g_signal_status;
		g_signal_status = 0;
	}
}

static t_bool	input_valid(char *input)
{
	if (!input)
	{
		printf("exit\n");
		return (FALSE);
	}
	return (TRUE);
}
