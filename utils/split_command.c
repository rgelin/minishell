/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:06:09 by jvander-          #+#    #+#             */
/*   Updated: 2021/11/02 14:13:10 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	**split_command(char *line)
{
	char	**command;

	command = ft_split(line, ' ');
	if (!command)
		return (NULL);
	if (!ft_strncmp(command[0], "cd", 2))
		return (ft_free(command, ft_tabsize(command)));
	return (command);
}
