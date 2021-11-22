
#include "minishell.h"

int	g_exit_code = 0;

#include <fcntl.h>
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
		env_cpy[i] = env[i];
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
	int	pid;
	int	pid2;
	int	p1[2];


void	ft_exit(char **cmd)
{
	char *arg;

	arg = cmd[1];
	if (arg)
	{
		if (arg[0] == '-')
			g_exit_code = ft_atoi(arg) + (256 * (g_exit_code / 256));
		else
			g_exit_code = ft_atoi(arg) - (256 * (g_exit_code / 256));
	}
	printf("exit\n");
	exit (g_exit_code);
}

void	update_shlvl(char ***env)
{
	int		i;
	int		lvl;
	char	*new_lvl;

	i = find_var_in_env("SHLVL", *env);
	lvl = ft_atoi_modified((*env)[i]);
	lvl++;
	new_lvl = ft_itoa(lvl);
	free((*env)[i]);
	(*env)[i] = NULL;
	(*env)[i] = ft_strjoin("SHLVL=", new_lvl);
	free(new_lvl);
	new_lvl = NULL;
}

void	ft_execute(t_exc *tab, int nbr_cmd)
{
	int	pid;
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
	t_pars *tab;
	t_exc	*exc;
	(void)argc;
	(void)argv;
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
	tab = NULL;
	new_env = cpy_env(env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sig_int);
	update_shlvl(&new_env);
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
		init_struct(state);
		rl_on_new_line();
		state->line = readline("\x1b[34mminishell > \x1b[0m");
		tab = parsing(state);
		exc = last_parsing(tab);
		if (!state->line)
		{
			// rl_replace_line("", 0);
			// d = 1;
			// free(state->line);
			// state->line = NULL;
			// rl_clear_history();
			// rl_replace_line("", 0);
			// rl_on_new_line();
			// rl_redisplay();
			// rl_replace_line("minishell > exit\n", 0);
			// rl_on_new_line();
			// rl_redisplay();

			printf("\x1b[34mminishell > \x1b[0mexit\n");
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
				if (ft_execute_command(exc[0], &new_env) == EXIT)
				{
					ft_free(new_env, ft_tabsize(new_env));
					ft_exit(state->command);
				}
				// rl_clear_history();
				ft_free(state->command, ft_tabsize(state->command));
				free(state->line);
			}
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
