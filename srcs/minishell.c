
#include "minishell.h"

void	init_struct(t_state *state)
{
	state->line = NULL;
	state->command = NULL;
	state->dq = NULL;
	state->sq = NULL;
	state->pipe = NULL;
	state->cmd = NULL;
	state->n_of_sq = 0;
	state->n_of_dq = 0;
	state->n_of_pipe = 0;
	state->eof = 0;
	state->n_of_dol = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_state *state;
	(void)argc;
	(void)argv;
	state = malloc(sizeof(t_state));
	if (!state)
		exit(EXIT_FAILURE);
	init_struct(state);
	while (1)
	{
		state->line = readline(">");
		add_history(state->line);
		parsing(state);
		state->command = ft_split(state->line, ' ');
		if (!state->command)
		{
			free(state->line);
			exit(1);
		}
		if (check_builtin(state->command[0]) == 0)
		{
			printf("minishell : %s command not found\n", state->command[0]);
			free(state->line);
			ft_free(state->command, ft_tabsize(state->command));
		}
		else
		{
			if (ft_execute_command(state->command, env) == EXIT)
			{
				free(state->line);
				ft_free(state->command, ft_tabsize(state->command));
				exit(EXIT);
			}
			ft_free(state->command, ft_tabsize(state->command));
			free(state->line);
		}
		//wait(0);
	}
	return (0);
}
