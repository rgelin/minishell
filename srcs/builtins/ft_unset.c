#include "../minishell.h"

void	ft_unset(t_exc exc, char ***env)
{
	char	**new_env;
	int		i;
	char	*arg;

	arg = exc.arg[0];
	if (!arg || !find_var_in_env(arg, *env))
		return ;
	// new_env = (char **)malloc(sizeof(char *) * (ft_tabsize(*env) + 1));
	new_env = ft_calloc(sizeof(char *), (ft_tabsize(*env) + 1));
	if (!new_env)
		exit(EXIT_FAILURE);
	i = -1;
	while ((*env)[++i])
	{
		if (i == find_var_in_env(arg, *env))
			i++;
		new_env[i] = ft_strdup((*env)[i]); //reste un leak ici
		if (!new_env[i])
			exit(EXIT_FAILURE);
	}
	new_env[i] = NULL;
	ft_free(*env, ft_tabsize(*env));
	*env = new_env;
}