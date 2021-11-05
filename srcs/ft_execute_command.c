
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
		exc = ft_export(cmd, exc);
		return (EXPORT);
	}
	if (check_builtin(cmd[0]) == UNSET)
		return (UNSET);
	if (check_builtin(cmd[0]) == ENV)
	{
		ft_env(exc);
		return (ENV);
	}
	return (EXIT);
}
