/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 08:39:43 by jvander-          #+#    #+#             */
/*   Updated: 2021/11/03 13:54:49 by rgelin           ###   ########.fr       */
/*   Updated: 2021/11/03 09:41:55 by jvander-         ###   ########.fr       */
/*   Updated: 2021/11/03 13:59:10 by jvander-         ###   ########.fr       */

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
