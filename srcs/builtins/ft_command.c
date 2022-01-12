/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:23:37 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/12 11:23:53 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_print_line(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	ft_echo(t_exc exc)
{
	if (exc.opt && ft_strchr(exc.opt, 'n'))
		ft_print_line(exc.arg);
	else if (ft_tabsize(exc.arg) < 1)
		ft_putchar_fd('\n', 1);
	else
	{
		ft_print_line(exc.arg);
		printf("\n");
	}
	g_global.exit_code = 0;
	return (ECHO);
}

int	ft_pwd(void)
{
	char	pwd[1024];

	g_global.exit_code = 0;
	if (!getcwd(pwd, 1024))
	{
		printf("minishell: pwd: %s\n", strerror(errno));
		g_global.exit_code = 1;
	}
	else
		printf("%s\n", pwd);
	return (PWD);
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	g_global.exit_code = 0;
	while (i < ft_tabsize(env))
	{
		if (ft_strchr_modified(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	return (ENV);
}

/*invalid read size of 8 ??*/
void	ft_exit(t_exc exc)
{
	if (exc.arg && exc.arg[1])
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		g_global.exit_code = 1;
		return ;
	}
	else if (exc.arg || exc.opt)
	{
		if (exc.opt != NULL)
			g_global.exit_code = ft_atoi(exc.opt)
				+ (256 * (ft_atoi(exc.opt) / 256));
		else if (exc.arg && check_str_digit(exc.arg[0]))
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n",
				exc.arg[0]);
			exit(255);
		}
		else
			g_global.exit_code = ft_atoi(exc.arg[0])
				- (256 * (ft_atoi(exc.arg[0]) / 256));
	}
	printf("exit\n");
}
