#include "../minishell.h"

void	ft_unset(t_exc exc, char ***env)
{
	char	**new_env;
	int		i;
	int		j;

	i = -1;
	if (exc.arg)
	{
		while (exc.arg[++i])
		{
			if (find_var_in_env(exc.arg[i], *env))
			{
				new_env = ft_calloc(sizeof(char *), (ft_tabsize(*env) + 1));
				if (!new_env)
					exit(EXIT_FAILURE);
				j = -1;
				while ((*env)[++j])
				{
					if (j == find_var_in_env(exc.arg[i], *env))
						j++;
					new_env[j] = ft_strdup((*env)[j]); //reste un leak ici
					if (!new_env[j])
						exit(EXIT_FAILURE);
				}
				new_env[j] = NULL;
				ft_free(*env, ft_tabsize(*env));
				*env = new_env;
			}
			// new_env = (char **)malloc(sizeof(char *) * (ft_tabsize(*env) + 1));

		}

	}
}