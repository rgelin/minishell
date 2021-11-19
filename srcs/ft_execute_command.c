
#include "minishell.h"

int	ft_execute_command(char **cmd, char ***env)
{
	if (check_builtin(cmd[0]) == ECHO)
	{
		ft_echo(cmd);
		return (ECHO);
	}
	if (check_builtin(cmd[0]) == CD)
	{
		ft_cd(cmd, env);
		return (CD);
	}
	if (check_builtin(cmd[0]) == PWD)
	{
		ft_pwd(cmd);
		return (PWD);
	}
	if (check_builtin(cmd[0]) == EXPORT)
	{
		ft_export(cmd, env);
		return (EXPORT);
	}
	if (check_builtin(cmd[0]) == UNSET)
	{
		ft_unset(cmd, env);
		return (UNSET);
	}
	if (check_builtin(cmd[0]) == ENV)
	{
		ft_env((*env));
		return (ENV);
	}
	return (EXIT);
}
