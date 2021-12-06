
#include "minishell.h"

extern int g_exit_code;

int	ft_execute_command(t_exc exc, char ***env)
{
	if (!ft_strncmp(exc.cmd, "echo", 5))
	{
		ft_echo(exc);
		return (ECHO);
	}
	if (!ft_strncmp(exc.cmd, "cd", 3))
	{
		ft_cd(exc, env);
		return (CD);
	}
	if (!ft_strncmp(exc.cmd, "pwd", 4))
	{
		ft_pwd();
		return (PWD);
	}
	if (!ft_strncmp(exc.cmd, "export", 7))
	{
		ft_export(exc, env);
		return (EXPORT);
	}
	if (!ft_strncmp(exc.cmd, "unset", 6))
	{
		ft_unset(exc, env);
		return (UNSET);
	}
	if (!ft_strncmp(exc.cmd, "env", 3))
	{
		ft_env((*env));
		return (ENV);
	}
	return (EXIT);
}
