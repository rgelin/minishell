/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:22:57 by jvander-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/12/06 14:27:54 by rgelin           ###   ########.fr       */
=======
/*   Updated: 2021/12/04 18:32:57 by rgelin           ###   ########.fr       */
>>>>>>> 9001a6883b68034a14a5db4cdf9a1f4f50ca2cd3
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	check_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4))
		return (ECHO);
	if (!ft_strncmp(cmd, "cd", 2))
		return (CD);
	if (!ft_strncmp(cmd, "pwd", 3))
		return (PWD);
	if (!ft_strncmp(cmd, "export", 6))
		return (EXPORT);
	if (!ft_strncmp(cmd, "unset", 5))
		return (UNSET);
	if (!ft_strncmp(cmd, "env", 3))
		return (ENV);
	if (!ft_strncmp(cmd, "exit", 4))
		return (EXIT);
	return (0);
}