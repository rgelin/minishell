
#include "minishell.h"

int	ft_execute_command(char **cmd, t_exc *exc)
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
	{
		ft_export(cmd, exc);
		int	i = -1;
		while (++i < ft_tabsize(exc->env_cpy))
			printf("%s\n", exc->env_cpy[i]);
		return (EXPORT);
	}
	if (check_builtin(cmd[0]) == UNSET)
		return (UNSET);
	if (check_builtin(cmd[0]) == ENV)
	{
		// int	i = -1;
		// while (++i < ft_tabsize(exc->env_cpy))
		// 	printf("\x1b[33m%s\x1b[0m\n", exc->env_cpy[i]);
		ft_env(exc->env_cpy);
		return (ENV);
	}
	return (EXIT);
}
