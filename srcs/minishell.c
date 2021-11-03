/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 08:39:43 by jvander-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/03 13:54:49 by rgelin           ###   ########.fr       */
=======
/*   Updated: 2021/11/03 09:41:55 by jvander-         ###   ########.fr       */
>>>>>>> 38d9213437f46299650c86e9ae8bb2a66962612e
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	**command;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline(">");
		command = ft_split(line, ' ');
		if (!command)
		{
			free(line);
			exit(1);
		}
		if (check_builtin(command[0]) == 0)
		{
			printf("minishell : %s command not found\n", command[0]);
			free(line);
			ft_free(command, ft_tabsize(command));
		}
		else
		{
			if (ft_execute_command(command, env) == EXIT)
			{
				free(line);
				ft_free(command, ft_tabsize(command));
				exit(EXIT);
			}
			ft_free(command, ft_tabsize(command));
			free(line);
		}
		wait(0);
	}
	return (0);
}
