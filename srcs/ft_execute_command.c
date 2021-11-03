/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:15:06 by jvander-          #+#    #+#             */
/*   Updated: 2021/11/03 09:41:22 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_command(char **cmd, char **env)
{
	if (check_builtin(cmd[0]) == ECHO)
	{
		ft_echo(cmd);
		return (ECHO);
	}
	if (check_builtin(cmd[0]) == CD)
		return (CD);
	if (check_builtin(cmd[0]) == PWD)
		return (PWD);
	if (check_builtin(cmd[0]) == EXPORT)
		return (EXPORT);
	if (check_builtin(cmd[0]) == UNSET)
		return (UNSET);
	if (check_builtin(cmd[0]) == ENV)
	{
		ft_env(env);
		return (ENV);
	}
	return (EXIT);
}
