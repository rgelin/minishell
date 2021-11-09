
#include "minishell.h"

void	init_struct(t_state *state)
{
	state->line = NULL;
	state->command = NULL;
	state->dq = NULL;
	state->sq = NULL;
}

char	**cpy_env(char **env)
{
	int i;
	char **env_cpy;

	env_cpy = (char **)malloc(sizeof(char *) * (ft_tabsize(env) + 1));
	if (!env_cpy)
		exit(EXIT_FAILURE);
	i = -1;
	while (env[++i])
		env_cpy[i] = ft_strdup(env[i]);
	env_cpy[i] = NULL;
	return (env_cpy);
}

int	main(int argc, char **argv, char **env)
{
	t_state *state;
	char	**new_env;
	(void)argc;
	(void)argv;
	state = malloc(sizeof(t_state));
	if (!state)
		exit(EXIT_FAILURE);
	signal(SIGQUIT, SIG_IGN);
	new_env = cpy_env(env);
	while (1)
	{
		rl_on_new_line();
		state->line = readline("\x1b[34mminishell > \x1b[0m");
		if (state->line == NULL)
		{
			rl_replace_line("", 0);
			rl_redisplay();
			rl_on_new_line();
			printf("\r\x1b[34mminishell > \x1b[0mexit\n");
			rl_clear_history();
			free(state->line);
			free(new_env);
			exit(EXIT_SUCCESS);
		}
		add_history(state->line);
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
			if (ft_execute_command(state->command, &new_env) == EXIT)
			{
				free(state->line);
				ft_free(state->command, ft_tabsize(state->command));
				exit(EXIT);
			}
			ft_free(state->command, ft_tabsize(state->command));
			free(state->line);
		}
	}
	return (0);
}
