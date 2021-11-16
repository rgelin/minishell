#include "../minishell.h"

void	ft_unset(char **cmd, char ***env)
{
	char	**new_env;
	int		i;
	char	*arg;

	arg = cmd[1];
	if (!arg || !find_var_in_env(arg, *env))
		return ;
	new_env = (char **)malloc(sizeof(char *) * (ft_tabsize(*env)));
	if (!new_env)
		exit(EXIT_FAILURE);
	i = -1;
	while ((*env)[++i])
	{
		if (i != find_var_in_env(arg, *env))
			new_env[i] = ft_strdup((*env)[i]);
	}
	ft_free(*env, ft_tabsize(*env));
	*env = new_env;
}