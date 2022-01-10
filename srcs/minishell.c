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
	init_global();
	update_shlvl(&new_env);
	signal(SIGQUIT, &ft_ctrl_backslash);
	signal(SIGINT, &ft_ctrl_c);
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
			exit(EXIT_FAILURE);
		}
		else if (state->line[0] != '\0')
		{
			tab = parsing(state);
			exc = last_parsing(tab, env);
			// char **heredoc = malloc(sizeof(char *) * 2);
			// heredoc[1] = NULL;
			// heredoc[0] = ft_strdup("ls");
			// exc[0].heredoc = heredoc;
			// exc[1].heredoc = NULL;
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
			{
				ft_execute_pipe(exc, tab->pipe, new_env);
			}
		}
		//system("leaks minishell");
	}
	//system("leaks minishell");
	return (0);
}
