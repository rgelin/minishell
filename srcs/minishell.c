
#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

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
		env_cpy[i] = strdup(env[i]);
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

int		check_str_digit(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-')
		i++;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
	}
	return (0);
}

void	ft_exit(t_exc exc) //invalid read size of 8 ??
{
	if (exc.arg && exc.arg[1])
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		g_exit_code = 1;
		return ;
	}
	else if (exc.arg || exc.opt)
	{
		if (exc.opt != NULL)
			g_exit_code = ft_atoi(exc.opt) + (256 * (ft_atoi(exc.opt) / 256));
		else if (exc.arg && check_str_digit(exc.arg[0]))
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", exc.arg[0]);
			exit(255);
		}
		else
			g_exit_code = ft_atoi(exc.arg[0]) - (256 * (ft_atoi(exc.arg[0]) / 256));
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

int	exec_pipe(t_exc *exc, char **env, int size)
{
	int		fd[2];
	pid_t	pid;
	int		i;
	int		oldfd = STDIN_FILENO;
	int		status;

	i = 0;
	while (i <= size)
	{
		if (pipe(fd) == -1)
		{
			perror("error pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("error fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			dup2(oldfd, STDIN_FILENO);
			close(oldfd);
			if (i <= size - 1)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			close(fd[0]);
			if (check_builtin(exc[i].cmd) != 0)
				status = ft_execute_command(exc[i], &env);
			else
				status = ft_exec(exc[i]);
			exit(status);
		}
		waitpid(pid, &status, 0);
		close(fd[1]);
		oldfd = fd[0];
		i++;
	}
	return (status);
}

int	main(int argc, char **argv, char **env)
{
	t_state *state;
	char	**new_env;
	t_pars *tab;
	t_exc	*exc;
	(void)argc;
	(void)argv;
	tab = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sig_int);
	state = malloc(sizeof(t_state));
	if (!state)
		exit(EXIT_FAILURE);
	new_env = cpy_env(env);
	update_shlvl(&new_env);
	while (1)
	{
		init_struct(state);
		rl_on_new_line();
		state->line = readline("\x1b[34mminishell > \x1b[0m");
		add_history(state->line);
		if (!state->line)
		{
			printf("\x1b[34mminishell > \x1b[0mexit\n");
			exit(g_exit_code);
		}
		else if (state->line[0] != '\0')
		{
			tab = parsing(state);
			exc = last_parsing(tab, env);
			if (tab->pipe == 0 && check_builtin(exc[0].cmd) == EXIT)
			{
				ft_free(new_env, ft_tabsize(new_env));
				free(exc);
				g_exit_code = 0;
				exit(g_exit_code);
			}
			g_exit_code = exec_pipe(exc, env, tab->pipe);
		}
	}
	return (0);
}

