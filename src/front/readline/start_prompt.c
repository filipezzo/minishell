
#include "minishell.h"

void	start_prompt(t_shell *shell)
{
	char		*input;
	char		*display;
	t_prompt	*prompt;

	prompt = new_prompt();
	while (TRUE)
	{
		// TODO: handler signals
		display = build_prompt(prompt);
		input = readline(display);
		if (!input || ft_strncmp(input, "exit", 4) == 0)
			break ;
		// TODO: handler input for command line structuring
		if (*input) // TODO: Should only add it if the cmd goes through the front process.
			add_history(input);
		(void)shell; // TODO: use in executer
		free(input);
		free(display);
	}
	free(input);
	free(display);
	destroy_prompt(prompt);
}
