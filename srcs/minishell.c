
#include "minishell.h"

int	g_exit_code = 0;

void	init_struct(t_state *state)
{
	state->line = NULL;
	state->pipe = NULL;
	state->cm = NULL;
	state->n_of_pipe = 0;
	state->eof = 0;
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
	t_pars *tab;
	t_exc	*exc;
	//char	**new_env;
	(void)argc;
	(void)argv;
	(void)env;
	state = malloc(sizeof(t_state));
	if (!state)
		exit(EXIT_FAILURE);
	/*
	exc = malloc(sizeof(t_exc));		//je mets ici pour l'instant pcq j'en ai besoin
	if (!exc)
		exit(EXIT_FAILURE);
	init_exc_struct(exc, env);
	*/
	tab = NULL;
	//init_struct(state);
	while (1)
	{
		init_struct(state);
		state->line = readline(">");
		add_history(state->line);
		//init_struct(state);
		tab = parsing(state);
		exc = last_parsing(tab);
		//free(tab);
		/*state->command = ft_split(state->line, ' ');
		if (!state->command)
		{
			free(state->line);
			exit(1);
		}
		if (check_builtin(state->command[0]) == 0)
	signal(SIGQUIT, SIG_IGN);
	new_env = cpy_env(env);
	while (1)
	{
		rl_on_new_line();
		state->line = readline("\x1b[34mminishell > \x1b[0m");
		if (state->line[0] != '\0')
		{
			add_history(state->line);
			state->command = ft_split(state->line, ' ');
			if (!state->command)
			{
				free(state->line);
				exit(1);
			}
			if (check_builtin(state->command[0]) == 0)
			{
				printf("minishell: %s: command not found\n", state->command[0]);
				g_exit_code = 127;
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
		//wait(0);*/
	}
	return (0);
}
