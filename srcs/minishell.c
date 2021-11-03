<<<<<<< HEAD
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 08:39:43 by jvander-          #+#    #+#             */
/*   Updated: 2021/11/03 13:59:10 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
>>>>>>> add history

#include "minishell.h"

void	init_struct(t_state *state)
{
	state->line = NULL;
	state->command = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_state *state;

	state = malloc(sizeof(t_state));
	if (!state)
		exit(EXIT_FAILURE);
	(void)argc;
	(void)argv;
	while (1)
	{
<<<<<<< HEAD
		state->line = readline(">");
		add_history(state->line);
		state->command = ft_split(state->line, ' ');
		if (!state->command)
=======
		line = readline(">");
		add_history(line);
		command = ft_split(line, ' ');
		if (!command)
>>>>>>> add history
		{
			free(state->line);
			exit(1);
		}
		if (check_builtin(state->command[0]) == 0)
		{
			printf("minishell : %s command not found\n", state->command[0]);
			free(state->line);
			ft_free(state->command, ft_tabsize(state->command));
		}
		else
		{
			if (ft_execute_command(state->command, env) == EXIT)
			{
				free(state->line);
				ft_free(state->command, ft_tabsize(state->command));
				exit(EXIT);
			}
			ft_free(state->command, ft_tabsize(state->command));
			free(state->line);
		}
		wait(0);
	}
	return (0);
}
