
#include "minishell.h"

static t_astree	*handle_front(char *input, t_lexsig **lexsigs);

void	start_prompt(t_shell *shell)
{
	char		*input;
	char		*display;
	t_prompt	*prompt;
	t_lexsig	**lexsigs;
	t_astree	*astree;

	prompt = new_prompt();
	lexsigs = new_lst_lexsig();
	while (TRUE)
	{
		// TODO: handler signals
		display = build_prompt(prompt);
		input = readline(display);
		if (!input || ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			free(display);
			break ;
		}
		astree = handle_front(input, lexsigs); // TODO: handler input for command line structuring
		print_astree(astree, STDOUT_FILENO);
		if (*input) // TODO: Should only add it if the cmd goes through the front process.
			add_history(input);
		(void)shell; // TODO: use in executer
		free(input);
		free(display);
		destroy_astree(astree);
	}
	destroy_lst_lexsig(lexsigs);
	destroy_prompt(prompt);
}

static t_astree	*handle_front(char *input, t_lexsig **lexsigs)
{
	t_dlist		*lextokens;
	t_astree	*astree;

	astree = NULL;
	lextokens = lexer(input, lexsigs);
	if (syntax_analyze(lextokens))
		astree = parser(lextokens);
	ft_destroy_dlist(lextokens);
	return (astree);
}
