/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:36:17 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/19 13:51:34 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_exit_opt(t_exc exc, int nbr_pipe)
{
	if (exc.regroup_exit == 1)
	{
		if (nbr_pipe == 0)
			printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		g_global.exit_code = 1;
	}
	else if (check_str_digit(exc.opt + 1))
	{
		if (nbr_pipe == 0)
			printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n",
			exc.opt);
		g_global.exit_code = 255;
	}
	else
		g_global.exit_code = ft_atoi(exc.opt)
			+ (256 * (ft_atoi(exc.opt) / 256));
}

static void	ft_exit_too_many_args(int nbr_pipe)
{
	if (nbr_pipe == 0)
		printf("exit\n");
	printf("minishell: exit: too many arguments\n");
	g_global.exit_code = 1;
}

static void	ft_exit_args(t_exc exc, int nbr_pipe)
{
	if (nbr_pipe == 0)
		printf("exit\n");
	if (check_str_digit(exc.arg[0]))
	{
		printf("minishell: exit: %s: numeric argument required\n",
			exc.arg[0]);
		g_global.exit_code = 255;
	}
	else
		g_global.exit_code = ft_atoi(exc.arg[0])
			- (256 * (ft_atoi(exc.arg[0]) / 256));
}

void	ft_exit(t_exc exc, int nbr_pipe)
{
	if (exc.opt)
	{
		ft_exit_opt(exc, nbr_pipe);
		return ;
	}
	else if (exc.regroup_exit || ft_tabsize(exc.arg) > 1)
	{
		ft_exit_too_many_args(nbr_pipe);
		return ;
	}
	else
	{
		ft_exit_args(exc, nbr_pipe);
		return ;
	}
	// if (nbr_pipe == 0)
		// printf("exit\n");
}