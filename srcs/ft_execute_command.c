
#include "minishell.h"

extern int g_exit_code;

int	ft_execute_command(t_exc exc, char ***env)
{
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
		ft_pwd();
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
