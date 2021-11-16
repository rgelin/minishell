
#include "minishell.h"
#include <fcntl.h>
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

void	ft_execute(int nbr_cmd)
{
	int	pid;
	int	p1[2];
	int	p2[2];

	if (pipe(p1))
	while (nbr_cmd)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			// recupere ce qu'il faut dans le pipe
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_state *state;
	char	**new_env;
	// int		p1[2];
	// int		p2[2];
	int		pid;
	t_exc	exc;
	// int		out;

	(void)argc;
	(void)argv;
	// if (pipe(p1) == 1)
		//exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		exc.cmd = "ls";
		exc.arg = NULL;
		exc.opt = NULL;
		// int file = open("plop", O_WRONLY | O_CREAT, 0777);
		// if (file == -1)
		// 	return (3);
		// //child
		// dup2(file, STDOUT_FILENO);
		// close(file);
		// if (read(p1[0], &exc, sizeof(exc)) == -1)
			// return (EXIT_FAILURE);
		if (check_builtin(exc.cmd) == 0)
			exit(ft_exec(exc));
		else
		{
			if (ft_execute_command(exc, &new_env) == EXIT)
				exit(EXIT);
		}
	}
	else
	{
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
			wait(NULL);
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
		}
		return (0);
}
