
#include "../minishell.h"

int	ft_execute_command(t_exc exc, char ***env)
{
	if (ft_check_error_arg_opt(exc))
		return (EXIT_FAILURE);
	if (check_builtin(exc.cmd) == ECHO)
		return (ft_echo(exc));
	if (check_builtin(exc.cmd) == CD)
		return (ft_cd(exc, env));
	if (check_builtin(exc.cmd) == PWD)
		return (ft_pwd());
	if (check_builtin(exc.cmd) == EXPORT)
		return (ft_export(exc, env));
	if (check_builtin(exc.cmd) == UNSET)
		return (ft_unset(exc, env));
	if (check_builtin(exc.cmd) == ENV)
		return (ft_env((*env)));
	return (EXIT);
}
