
#include "minishell.h"

int	g_exit_code = 0;

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

void	ft_sigint()
{
	g_exit_code = -1;
	printf("\n");
	// rl_replace_line("\x1b[34mminishell > \x1b[0m", 0);
	// rl_redisplay();
	// printf("%d\n", g_exit_code);
}

int	main(int argc, char **argv, char **env)
{
	t_state *state;
	char	**new_env;
	int		go;
	// char	buf[256];
	(void)argc;
	(void)argv;
	state = malloc(sizeof(t_state));
	if (!state)
		exit(EXIT_FAILURE);
	new_env = cpy_env(env);
	signal(SIGQUIT, SIG_IGN);
	go = 1;
	signal(SIGINT, ft_sigint);
	while (go)
	{
		// go = ft_ctrl_d();
		rl_on_new_line();
		state->line = readline("\x1b[34mminishell > \x1b[0m");
		if (!state->line)
		{
			go = 0;
			printf("\x1b[34mminishell > \x1b[0mexit\n");
			exit(EXIT_SUCCESS);
		}
		else if (state->line[0] != '\0')
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
		printf("%d\n", g_exit_code);
		if (g_exit_code == -1)
			g_exit_code = 0;
		// go = ft_ctrl_d();
	}
	return (0);
}
