
#include "minishell.h"

int	g_exit_code = 0;

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
	int		d;
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
	}
	new_env = cpy_env(env);
	signal(SIGQUIT, SIG_IGN);
	d = 0;
	signal(SIGINT, ft_sig_int);
	update_shlvl(&new_env);
	while (1)
	{
		rl_on_new_line();
		state->line = readline("\x1b[34mminishell > \x1b[0m");
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
				if (ft_execute_command(exc, &new_env) == EXIT)
				{
					ft_free(new_env, ft_tabsize(new_env));
					ft_exit(state->command);
				}
				// rl_clear_history();
				ft_free(state->command, ft_tabsize(state->command));
				free(state->line);
			}
		}
		return (0);
}
