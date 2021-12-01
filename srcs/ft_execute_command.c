
#include "minishell.h"

int	ft_execute_command(t_exc exc, char ***env)
{
	// char **new_cmd;

	// new_cmd = create_cmd(cmd);
	if (check_builtin(exc.cmd) == ECHO)
	{
		ft_echo(exc);
		return (ECHO);
	}
	if (check_builtin(exc.cmd) == CD)
	{
		ft_cd(exc, env);
		return (CD);
	}
	if (check_builtin(exc.cmd) == PWD)
	{
		ft_pwd(exc);
		return (PWD);
	}
	if (check_builtin(exc.cmd) == EXPORT)
	{
		ft_export(exc, env);
		return (EXPORT);
	}
	if (check_builtin(exc.cmd) == UNSET)
	{
		ft_unset(exc, env);
		return (UNSET);
	}
	if (check_builtin(exc.cmd) == ENV)
	{
		ft_env((*env));
		return (ENV);
	}
	return (EXIT);
}
