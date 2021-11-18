
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

void	ft_echo(char **cmd)
{
	if (ft_tabsize(cmd) < 2)
		return ;
	if (!ft_strncmp(cmd[1], "$?", 2))
	{
		printf("%d\n", g_exit_code);
		g_exit_code = 0;
		return ;
	}
	if (!ft_strncmp(cmd[1], "-n", 2))
		ft_print_line(cmd, 2);
	else
	{
		ft_print_line(cmd, 1);
		printf("\n");
	}
}

void	ft_pwd(char **cmd)
{
	char	pwd[1024]; //redefinir la taille en mode bien

	if (cmd[1]) //pour l'instant protecion comme ca mais a voir avec les pipes pour plusieurs arguments
	{
		write (2, "pwd: too many arguments\n", 24); //faire une fonction de gestion d'erreur (avec perror je pense)
		return ;
	}
	printf("%s\n", getcwd(pwd, 1024));
}

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (i < ft_tabsize(env))
	{
		if (ft_strchr_modified(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
}
