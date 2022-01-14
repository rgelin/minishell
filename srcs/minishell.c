/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:33:59 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/14 12:09:05 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

static void	ft_execute_line(t_exc *exc, t_pars *tab, char **new_env)
{
	int	n_pipe;
	int	*fds;

	n_pipe = 0;
	ft_open_pipes(tab->pipe, &fds);
	ft_exec_heredoc(tab->pipe, exc, fds, n_pipe);
	if (!exc->heredoc && check_builtin(exc->cmd) != ECHO)
		g_global.exit_code = 0;
	ft_create_all_redirect(exc, tab->pipe);
	if (tab->pipe == 0 && check_builtin(exc[0].cmd) == EXIT)
	{
		ft_free(new_env, ft_tabsize(new_env));
		ft_exit(exc[0]);
		ft_free_tab_exc(exc, tab);
		exit(g_global.exit_code);
	}
	if (tab->pipe == 0 && (check_builtin(exc[0].cmd) == CD
			|| check_builtin(exc[0].cmd) == EXPORT
			|| check_builtin(exc[0].cmd) == UNSET))
		ft_execute_command(exc[0], &new_env);
	else
		ft_execute_pipe(exc, tab->pipe, new_env, fds);
}

void	ft_prompt(t_state *state)
{
	g_global.fork_pid = 0;
	init_struct(state);
	rl_on_new_line();
	(state)->line = readline("\x1b[34mminishell > \x1b[0m");
	add_history(state->line);
	ft_ctrl_d(state);
	if (state && state->line[0] == '\0')
	{
		free(state->line);
		state->line = NULL;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_state	*state;
	char	**new_env;
	t_pars	*tab;
	t_exc	*exc;

	(void)argc;
	(void)argv;
	new_env = cpy_env(env);
	init_variables(&state, &tab, &exc);
	update_shlvl(&new_env);
	ft_signal();
	while (1)
	{
		ft_prompt(state);
		if (state->line && state->line[0] != '\0')
		{
			tab = parsing(state);
			if (tab)
			{
				exc = last_parsing(tab, env);
				ft_execute_line(exc, tab, new_env);
				ft_free_tab_exc(exc, tab);
			}
			//ft_free_tab_exc(exc, tab);
		}
	}
	return (0);
}
