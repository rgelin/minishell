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

/*pas le seul exit code --> recup les exit code d'execv*/

void	ft_free_tab_exc(t_exc *last_tab, t_pars *tab)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (last_tab)
	{
		while (i <= tab->pipe)
		{
			if (last_tab[i].cmd)
				free(last_tab[i].cmd);
			if (last_tab[i].opt)
				free(last_tab[i].opt);
			j = 0;
			if (last_tab[i].redirect[j])
			{
		 		while(last_tab[i].redirect[j] != NULL)
		 		{
		 			free(last_tab[i].redirect[j]);
		 			j++;
		 		}
			}
			j = 0;
			if (last_tab[i].arg[j])
			{
	  			while(last_tab[i].arg[j] != NULL)
	  			{
	  				free(last_tab[i].arg[j]);
	  				j++;
		 		}
			}
			i++;
		}
	}
	//free(last_tab);
	//free(tab);
}

void	ft_signal_msg(int exit_code)
{
	if (exit_code == 131)
		ft_putendl_fd("QUIT: 3", 1);
	if (exit_code == 130)
		ft_putchar_fd('\n', 1);
}

void	ft_ctrl_c(void)
{
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_code = 1;
}

void	ft_ctrl_backslash(void)
{
	rl_on_new_line();
	// rl_redisplay();
}

void	ft_signal(int signal)
{
	if (signal == SIGINT)
		ft_ctrl_c();
	if (signal == SIGQUIT)
		ft_ctrl_backslash();
}

int	main(int argc, char **argv, char **env)
{
	t_state	*state;
	char	**new_env;
	t_pars	*tab;
	t_exc	*exc;

	(void)argc;
	(void)argv;
	tab = NULL;
	state = NULL;
	new_env = cpy_env(env);
	state = malloc(sizeof(t_state));
	if (!state)
		exit(EXIT_FAILURE);
	new_env = cpy_env(env);
	update_shlvl(&new_env);
	signal(SIGQUIT, &ft_signal);
	signal(SIGINT, &ft_signal);
	while (1)
	{
		init_struct(state);
		rl_on_new_line();
		state->line = readline("\x1b[34mminishell > \x1b[0m");
		add_history(state->line);
		if (!state->line)
		{
			printf("exit\n");
			// printf("\x1b[34mminishell > \x1b[0mexit\n");
			//ft_free_tab_exc(exc, tab);
			exit(g_exit_code);
		}
		else if (state->line[0] != '\0')
		{
			tab = parsing(state);
			exc = last_parsing(tab, env);
			if (tab->pipe == 0 && check_builtin(exc[0].cmd) == EXIT)
			{
				ft_free(new_env, ft_tabsize(new_env));
				ft_exit(exc[0]);
				ft_free_tab_exc(exc, tab);
				exit(g_exit_code);
			}
			if (tab->pipe == 0 && (check_builtin(exc[0].cmd) == CD ||
				check_builtin(exc[0].cmd) == EXPORT || check_builtin(exc[0].cmd) == UNSET))
			{
				if (ft_execute_command(exc[0], &new_env) == EXIT)
				{
					printf("minishell : %s: command not found\n", exc[0].cmd);
					g_exit_code = 127;
				}
			}
			else
				g_exit_code = exec_pipe(exc, &new_env, tab->pipe);
		}

	}
	return (0);
}
