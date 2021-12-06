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
void	ft_sig_int(int signal)
{
	(void)signal;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_exit_code <= 1)
		rl_redisplay();
	g_exit_code = 1;
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
	new_env = cpy_env(env);
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
				ft_exit(exc[0]);
				free(exc);
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
