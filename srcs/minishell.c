
#include "minishell.h"

void	init_struct(t_state *state)
{
	state->line = NULL;
	state->command = NULL;
	state->dq = NULL;
	state->sq = NULL;
	state->pipe = NULL;
	//state->cmd = NULL;
	state->dol = NULL;
	state->opt = NULL;
	state->lchv = NULL;
	state->rchv = NULL;
	state->n_of_sq = 0;
	state->n_of_dq = 0;
	state->n_of_pipe = 0;
	state->eof = 0;
	state->n_of_dol = 0;
	state->n_of_opt = 0;
	state->n_of_lchv = 0;
	state->n_of_rchv = 0;
}

char	**cpy_env(char **env)
{
	int i;
	char **env_cpy;

	env_cpy = (char **)malloc(sizeof(char *) * ft_tabsize(env) + 1);
	if (!env_cpy)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < ft_tabsize(env))
		env_cpy[i] = env[i];
	return (env_cpy);
}

void	init_exc_struct(t_exc *exc, char **env)
{
	exc->env_cpy = cpy_env(env);
}

int	main(int argc, char **argv, char **env)
{
	t_state *state;
	t_pars *tab;
	//t_exc	*exc;
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
	init_struct(state);
	while (1)
	{
		state->line = readline(">");
		add_history(state->line);
		//init_struct(state);
		tab = parsing(state);
		free(tab);
		/*state->command = ft_split(state->line, ' ');
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
			if (ft_execute_command(state->command, exc) == EXIT)
			{
				free(state->line);
				ft_free(state->command, ft_tabsize(state->command));
				exit(EXIT);
			}
			ft_free(state->command, ft_tabsize(state->command));
			free(state->line);
		}
		//wait(0);*/
	}
	return (0);
}
