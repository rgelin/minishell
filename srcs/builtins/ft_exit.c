/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:36:17 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/20 12:54:55 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*our_getenv_bis(char *line, char **env)
{
	int		index;
	char	*var;
	char	*tmp;
	char	**test;

	var = NULL;
	test = NULL;
	tmp = NULL;
	index = find_var_in_env(line, env);
	if (index >= 0)
	{
		var = env[index];
		test = ft_split(var, '=');
		if (ft_tabsize(test) > 1)
			tmp = ft_strdup(test[1]);
	}
	if (index == -1)
		tmp = ft_strdup("");
	index = -1;
	while (test && test[++index])
		free(test[index]);
	if (test)
		free(test);
	free(line);
	return (ft_strtrim(tmp, " "));
}

static void	ft_exit_opt(t_exc exc, int nbr_pipe)
{
	if (exc.regroup_exit == 1)
	{
		if (nbr_pipe == 0)
			printf("exit\n");
		ft_perror(exc.cmd, NULL, "too many arguments");
		g_global.exit_code = 1;
	}
	else if (check_str_digit(exc.opt + 1))
	{
		if (nbr_pipe == 0)
			printf("exit\n");
		ft_perror(exc.cmd, exc.opt, "numeric argument required");
		g_global.exit_code = 255;
	}
	else
		g_global.exit_code = ft_atoi(exc.opt)
			+ (256 * (ft_atoi(exc.opt) / 256));
}

static void	ft_exit_too_many_args(t_exc exc, int nbr_pipe)
{
	if (nbr_pipe == 0)
		printf("exit\n");
	ft_perror(exc.cmd, NULL, "too many arguments");
	g_global.exit_code = 1;
}

static void	ft_exit_args(t_exc exc, int nbr_pipe)
{
	if (nbr_pipe == 0)
		printf("exit\n");
	if (check_str_digit(exc.arg[0]))
	{
		ft_perror(exc.cmd, exc.opt, "numeric argument required");
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
		ft_exit_too_many_args(exc, nbr_pipe);
		return ;
	}
	else
	{
		ft_exit_args(exc, nbr_pipe);
		return ;
	}
}
