#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
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
			if (last_tab[i].redirect && last_tab[i].redirect[j])
			{
				while(last_tab[i].redirect[j] != NULL)
				{
					free(last_tab[i].redirect[j]);
					j++;
				}
			}
			j = 0;
			if (last_tab[i].arg && last_tab[i].arg[j])
			{
				while(last_tab[i].arg[j] != NULL)
				{
					free(last_tab[i].arg[j]);
					j++;
				}
			}
			j = 0;
			if (last_tab[i].heredoc && last_tab[i].heredoc[j])
			{
				while(last_tab[i].heredoc[j] != NULL)
				{
					free(last_tab[i].heredoc[j]);
					j++;
				}
			}
			i++;
		}
	}
	//free(last_tab);
	//free(tab);
}

void	init_global(void)
{
	g_global.exit_code = 0;
	g_global.fork_pid = 0;
	g_global.in_heredoc = 0;
}

void	init_variables(t_state **state, t_pars **tab, t_exc **exc)
{
	*tab = NULL;
	*state = NULL;
	*exc = NULL;
	*state = malloc(sizeof(t_state));
	if (!*state)
		exit(EXIT_FAILURE);
	init_global();
}

void	ft_execute_line(t_exc *exc, t_pars *tab, char **new_env)
{
	ft_create_all_redirect(exc, tab->pipe);
	if (tab->pipe == 0 && check_builtin(exc[0].cmd) == EXIT)
	{
		ft_free(new_env, ft_tabsize(new_env));
		ft_exit(exc[0]);
		ft_free_tab_exc(exc, tab);
		exit(g_global.exit_code);
	}
	if (tab->pipe == 0 && (check_builtin(exc[0].cmd) == CD
		|| check_builtin(exc[0].cmd) == EXPORT || check_builtin(exc[0].cmd) == UNSET))
		ft_execute_command(exc[0], &new_env);
	else
		ft_execute_pipe(exc, tab->pipe, new_env);
}

void	ft_signal(void)
{
	signal(SIGQUIT, &ft_ctrl_backslash);
	signal(SIGINT, &ft_ctrl_c);
}

void	ft_ctrl_d(t_state *state, t_exc *exc, t_pars *tab)
{
	if (!state->line)
	{
		printf("exit\n");
		ft_free_tab_exc(exc, tab);
		exit(EXIT_FAILURE);
	}
}

void	ft_prompt(t_state **state, t_exc *exc, t_pars *tab)
{
	g_global.fork_pid = 0;
	init_struct(*state);
	rl_on_new_line();
	(*state)->line = readline("\x1b[34mminishell > \x1b[0m");
	add_history((*state)->line);
	ft_ctrl_d(*state, exc, tab);
}

int	main(int argc, char **argv, char **env)
{
	t_state	*state;
	char	**new_env;
	t_pars	*tab;
	t_exc	*exc;

	(void)argc;
	(void)argv;
	init_variables(&state, &tab, &exc);
	new_env = cpy_env(env);
	update_shlvl(&new_env);
	// printf("%s\n", getenv(env[find_var_in_env("SHLVL", env)]));
	// if (!ft_strncmp(getenv(env[find_var_in_env("SHLVL", env)]), "1", 1))
	ft_signal();
	while (1)
	{
		ft_prompt(&state, exc, tab);
		if (state->line[0] != '\0')
		{
			tab = parsing(state);
			exc = last_parsing(tab, env);
			ft_execute_line(exc, tab, new_env);
		}
	}
	return (0);
}
