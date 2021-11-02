/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:22:57 by jvander-          #+#    #+#             */
/*   Updated: 2021/11/02 11:04:01 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	check_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4))
		return (1);
	if (!ft_strncmp(cmd, "cd", 2))
		return (2);
	if (!ft_strncmp(cmd, "pwd", 3))
		return (3);
	if (!ft_strncmp(cmd, "export", 6))
		return (4);
	if (!ft_strncmp(cmd, "unset", 5))
		return (5);
	if (!ft_strncmp(cmd, "env", 3))
		return (6);
	if (!ft_strncmp(cmd, "exit", 4))
		return (7);
	return (0);
}