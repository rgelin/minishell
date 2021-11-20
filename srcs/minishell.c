
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

void	ft_sig_int()
{
	g_exit_code = 1; //pas le seul exit code --> recup les exit code d'execv
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	t_state *state;
	char	**new_env;
	// char	buf[256];
	(void)argc;
	(void)argv;
	state = malloc(sizeof(t_state));
	if (!state)
		exit(EXIT_FAILURE);
	new_env = cpy_env(env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sig_int);
	while (1)
	{
		// go = ft_ctrl_d();
		rl_on_new_line();
		state->line = readline("\x1b[34mminishell > \x1b[0m");
		if (!state->line)
		{
			rl_replace_line("", 0);
			rl_replace_line("minishell > exit\n", 1);
			rl_redisplay();
			// printf("\x1b[34mminishell > \x1b[0mexit\n");
			exit(EXIT_SUCCESS);
		}
		else if (state->line[0] != '\0')
		{
			add_history(state->line);
			state->command = ft_split(state->line, ' ');
			if (!state->command)
				exit(EXIT_FAILURE);
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
					printf("%s\n", (unsigned char *)state->command[1]);
					printf("%d\n", (unsigned int)ft_atoi(state->command[1]));
					printf("%d\n", (unsigned int)((unsigned int)256-(unsigned int)258));
		
					// if (state->command[1])
					// 	g_exit_code = (unsigned int)ft_atoi(state->command[1]);
					// free(state->line);
					// ft_free(state->command, ft_tabsize(state->command));
					// printf("%d\n", g_exit_code);
					printf("exit\n");
					exit(g_exit_code);
				}

				ft_free(state->command, ft_tabsize(state->command));
				free(state->line);
			}
		}
		// printf("%d\n", g_exit_code);
		// if (g_exit_code == -1)
		// {
		// 	printf("\n");
		// 	rl_on_new_line();
		// 	state->line = readline("\x1b[34mminishell > \x1b[0m");
		// 	g_exit_code = 0;
		// }
		// go = ft_ctrl_d();
	}
	return (0);
}
