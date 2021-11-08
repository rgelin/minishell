
#include "minishell.h"

char	**ft_realloc_env(char ***env, int size)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc(sizeof(char *) * (ft_tabsize((*env)) + size));
	if (!new_env)
		exit(EXIT_FAILURE);
	i = -1;
	while ((*env)[++i])
		new_env[i] = (*env)[i];
	return (new_env);
}

char	*ft_cpy_str(char **cmd, char ***new_env)
{
	char	*cmd_cpy;

	cmd_cpy = (char *)malloc(sizeof(char) * (ft_strlen(cmd[1]) + 1));
	if (!cmd_cpy)
	{
		free(*new_env);
		*new_env = NULL;
		exit(EXIT_FAILURE);
	}
	int j = -1;
	while (cmd[1][++j])
		cmd_cpy[j] = cmd[1][j];
	cmd_cpy[j] = '\0';
	return (cmd_cpy);
}

void	ft_export(char **cmd, char ***env)
{
	char	**new_env;
	char	*temp;
	char	*cmd_cpy;

	(void)cmd;
	if (!ft_strchr(cmd[1], '='))
		return ;
	else
	{
		new_env = ft_realloc_env(env, 2);
		cmd_cpy = ft_cpy_str(cmd, &new_env);
		
		new_env[ft_tabsize(*env)] = cmd_cpy;
		new_env[ft_tabsize(*env) + 1] = NULL;

		temp = new_env[ft_tabsize(new_env) - 2];
		new_env[ft_tabsize(new_env) - 2] = new_env[ft_tabsize(new_env) - 1];
		new_env[ft_tabsize(new_env) - 1] = temp;

		free((*env));
		(*env) = NULL;
		(*env) = new_env;
	}
}
