/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 08:39:43 by jvander-          #+#    #+#             */
/*   Updated: 2021/11/02 14:16:27 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
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
			if (ft_execute_command(command) == EXIT)
			{
				free(line);
				ft_free(command, ft_tabsize(command));
				exit(EXIT);
			}
		}
		wait(0);
	}
	return (0);
}
