/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:15:06 by jvander-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/02 16:58:15 by rgelin           ###   ########.fr       */
=======
/*   Updated: 2021/11/03 09:41:22 by jvander-         ###   ########.fr       */
>>>>>>> 38d9213437f46299650c86e9ae8bb2a66962612e
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
	{
		ft_env(env);
		return (ENV);
	}
	return (EXIT);
}
