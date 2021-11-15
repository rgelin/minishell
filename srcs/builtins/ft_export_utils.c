
#include "../minishell.h"

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
	int		j;

	cmd_cpy = (char *)malloc(sizeof(char) * (ft_strlen(cmd[1]) + 1));
	if (!cmd_cpy)
	{
		free(*new_env);
		*new_env = NULL;
		exit(EXIT_FAILURE);
	}
	j = -1;
	while (cmd[1][++j])
		cmd_cpy[j] = cmd[1][j];
	cmd_cpy[j] = '\0';
	return (cmd_cpy);
}

int	find_var_in_env(char **cmd, char **env)
{
	int	index;
	int	i;
	int	j;

	index = 0;
	i = -1;
	j = 0;
	while (cmd[1][j] && cmd[1][j] != '+' && cmd[1][j] != '=')
		j++;
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(cmd[1], env[i], j - 1))
			return (i);
	}
	return (0);
}

//we check if the exact same argument already exist in env (add +1 strncmp in of just "ARG=")
int		check_if_already_in_env(char **cmd, char ***env)
{
	int i;

	i = -1;
	// printf("strlen: %d\n", (int)ft_strlen(cmd[1]));
	while (cmd[1] && (*env)[++i])
	{
		if (!ft_strncmp(cmd[1], (*env)[i], ft_strlen(cmd[1]) + 1))
			return (1);
	}
	return (0);
}
