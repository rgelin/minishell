/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:15:06 by jvander-          #+#    #+#             */
/*   Updated: 2021/11/02 16:58:15 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_command(char **cmd)
{
	if (check_builtin(cmd[0]) == ECHO)
	{
		ft_echo(cmd);
		return (ECHO);
	}
	if (check_builtin(cmd[0]) == CD)
	{
		ft_cd(cmd);
		return (CD);
	}
	if (check_builtin(cmd[0]) == PWD)
	{
		ft_pwd(cmd);
		return (PWD);
	}
	if (check_builtin(cmd[0]) == EXPORT)
		return (EXPORT);
	if (check_builtin(cmd[0]) == UNSET)
		return (UNSET);
	if (check_builtin(cmd[0]) == ENV)
		return (ENV);
	return (EXIT);
}
