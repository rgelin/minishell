
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
		env_cpy[i] = env[i];
	env_cpy[i] = NULL;
	return (env_cpy);
}

void	ft_execute(t_exc *tab)
{
	int	*pid;
	int	pid2;
	int	p1[2];

	if (pipe(p1) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{ //CHILD
		close(p1[0]);
		dup2(p1[1], STDOUT_FILENO);
		close(p1[1]);
		ft_exec(tab[0]);
		exit(EXIT_SUCCESS);
	}
	pid2 = fork();
	if (pid2 == -1)
		exit(EXIT_FAILURE);
	if (pid2 == 0)
	{ //CHILD 2
		close(p1[1]);
		dup2(p1[0], STDIN_FILENO);
		close(p1[0]);
		ft_exec(tab[1]);
		exit(EXIT_SUCCESS);
	}
	close(p1[0]);
	close(p1[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv, char **env)
{
	t_state *state;
	char	**new_env;
	t_exc	*exc;

	// char **arg = (char**)malloc(sizeof(char *) * 3);
	// arg[0] = ft_strdup("plop");
	// arg[1] = ft_strdup("lol");
	// arg[2] = NULL;
	exc = malloc(sizeof(t_exc) * 4);
	(void)argc;
	(void)argv;
	exc[0].cmd = "ls";
	exc[0].arg = NULL;
	exc[0].opt = NULL;
	exc[1].cmd = "ls";
	exc[1].arg = NULL;
	exc[1].opt = "-l";
	exc[2].cmd = "ls";
	exc[2].arg = NULL;
	exc[2].opt = NULL;
	exc[3].cmd = NULL;
	exc[3].opt = NULL;
	exc[3].arg = NULL;
		
		// if (check_builtin(exc.cmd) == 0)
			// exit(ft_exec(exc));
		// else
		// {
			// if (ft_execute_command(exc, &new_env) == EXIT)
				// exit(EXIT);
		// }
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
		ft_exec(exc[1]);
		// ft_execute(exc);
	// 	if (check_builtin(state->command[0]) == 0)
	// 	{
	// 		printf("minishell : %s command not found\n", state->command[0]);
	// 		free(state->line);
	// 		ft_free(state->command, ft_tabsize(state->command));
	// 	}
	// 	else
	// 	{
	// 		if (ft_execute_command(state->command, &new_env) == EXIT)
	// 		{
	// 			free(state->line);
	// 			ft_free(state->command, ft_tabsize(state->command));
	// 			exit(EXIT);
	// 		}
	// 		ft_free(state->command, ft_tabsize(state->command));
	// 		free(state->line);
	// 	}
	}
	return (0);
}
