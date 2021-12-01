
#include "../minishell.h"

extern int	g_exit_code;

static void	ft_print_line(char **cmd, int i)
{
	char	*str_trim;

	while (cmd[i])
	{
		str_trim = ft_strtrim(cmd[i], "\"");
		printf("%s", str_trim);
		if (cmd[i + 1])
			printf(" ");
		i++;
		free(str_trim);
	}
}

void	ft_echo(t_exc exc)
{
	if (ft_tabsize(exc.arg) < 1)
		printf("\n");
	else if (!ft_strncmp(exc.arg[0], "$?", 2))
		printf("%d\n", g_exit_code);
	else if (exc.opt && !ft_strncmp(exc.opt, "-n", 3))
		ft_print_line(exc.arg, 1);
	else
	{
		ft_print_line(exc.arg, 0);
		printf("\n");
	}
	g_exit_code = 0;
}

void	ft_pwd()
{
	char	pwd[1024];

	g_exit_code = 0;
	if (!getcwd(pwd, 1024))
	{
		printf("minishell: pwd: %s\n", strerror(errno));
		g_exit_code = 1;
	}
	else
		printf("%s\n", pwd);
}

void	ft_env(char **env)
{
	int	i;

	i = 0;
	g_exit_code = 0;
	while (i < ft_tabsize(env))
	{
		if (ft_strchr_modified(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
}
