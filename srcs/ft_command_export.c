
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

int		check_if_in_env(char **cmd, char ***env)
{
	int i;

	i = -1;
	while ((*env)[++i])
	{
		if (!ft_strncmp(cmd[1], (*env)[i], ft_strlen(cmd[1])))
			return (1);
	}
	return (0);
}

int		check_change_in_env(char **cmd, char ***env)
{
	char	*temp;
	int		i;

	i = -1;
	temp = malloc(sizeof(char) * ft_strlen(cmd[1]) + 1);
	if (!temp)
	{
		free(*env);
		*env = NULL;
		exit(EXIT_FAILURE);
	}
	while (cmd[1][++i] != '=')
		temp[i] = cmd[1][i];
	temp[i] = '\0';
	i = -1;
	while ((*env)[++i])
	{
		if (!ft_strncmp(temp, (*env)[i], ft_strlen(temp)))
			return (1);
	}
	return (0);
}

void	modify_var_in_env(char **cmd, char ***env)
{
	char	*temp;
	int		i;
	int		j;

	j = -1;
	while (cmd[1][j] != '=')
		j++;
	i = -1;
	while ((*env)[++i])
	{
		if (!ft_strncmp(cmd[1], (*env)[i], j))
			break ;
	}
	temp = malloc(sizeof(char) * ft_strlen(cmd[1]) + 1);
	if (!temp)
	{
		free(*env);
		*env = NULL;
		exit(EXIT_FAILURE);
	}
	j = -1;
	while (cmd[1][++j])
		temp[j] = cmd[1][j];
	temp[j] = '\0';
	free((*env)[i]);
	(*env)[i] = NULL;
	(*env)[i] = temp;
}

void	ft_export(char **cmd, char ***env)
{
	char	**new_env;
	char	*temp;
	char	*cmd_cpy;

	if (!ft_strchr(cmd[1], '='))
		return ;
	else if (check_if_in_env(cmd, env))
		return ;
	else if (check_change_in_env(cmd, env))
		modify_var_in_env(cmd, env);
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
