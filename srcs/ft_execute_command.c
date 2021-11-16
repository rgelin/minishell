
#include "minishell.h"

int	ft_execute_command(t_exc cmd, char ***env)
{
	char **new_cmd;

	new_cmd = create_cmd(cmd);
	if (check_builtin(new_cmd[0]) == ECHO)
	{
		ft_echo(new_cmd);
		return (ECHO);
	}
	if (check_builtin(new_cmd[0]) == CD)
	{
		ft_cd(new_cmd, env);
		return (CD);
	}
	if (check_builtin(new_cmd[0]) == PWD)
	{
		ft_pwd(new_cmd);
		return (PWD);
	}
	if (check_builtin(new_cmd[0]) == EXPORT)
	{
		ft_export(new_cmd, env);
		return (EXPORT);
	}
	if (check_builtin(new_cmd[0]) == UNSET)
	{
		ft_unset(new_cmd, env);
		return (UNSET);
	}
	if (check_builtin(new_cmd[0]) == ENV)
	{
		ft_env((*env));
		return (ENV);
	}
	return (EXIT);
}
