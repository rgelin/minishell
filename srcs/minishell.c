
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

int		check_str_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
	}
	return (0);
}

void	ft_exit(char **cmd) //invalid read size of 8 ??
{
	char *arg;

	arg = cmd[1];
	if (cmd[2])
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		g_exit_code = 1;
		return ;
	}
	else if (arg)
	{
		if (check_str_digit(arg))
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", arg);
			exit(255);
		}
		else if (arg[0] == '-')
			g_exit_code = ft_atoi(arg) + (256 * (ft_atol(arg) / 256));
		else
			g_exit_code = ft_atoi(arg) - (256 * (ft_atoi(arg) / 256));
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

int	main(int argc, char **argv, char **env)
{
	t_state *state;
	char	**new_env;
	int		d;
	(void)argc;
	(void)argv;
	state = malloc(sizeof(t_state));
	if (!state)
		exit(EXIT_FAILURE);
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
				if (ft_execute_command(state->command, &new_env) == EXIT)
				{
					ft_free(new_env, ft_tabsize(new_env));
					rl_clear_history();
					ft_exit(state->command);
				}
				ft_free(state->command, ft_tabsize(state->command));
				free(state->line);
			}
		}
	}
	return (0);
}
