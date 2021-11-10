
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

//we check if the exact same argument already exist in env (add +1 strncmp in of just "ARG=")
int		check_if_already_in_env(char **cmd, char ***env)
{
	int i;

	i = -1;
	while (cmd[1] && (*env)[++i])
	{
		if (!ft_strncmp(cmd[1], (*env)[i], (ft_strlen(cmd[1]) + 1)))
			return (1);
	}
	return (0);
}

//we check if we already have the argument as enviroment variable
int		check_if_in_env(char **cmd, char ***env)
{
	char	*temp;
	int		i;

	i = -1;
	temp = malloc(sizeof(char) * (ft_strlen(cmd[1]) + 1));
	if (!temp)
	{
		free(*env);
		*env = NULL;
		exit(EXIT_FAILURE);
	}
	while (cmd[1][++i] && cmd[1][i] != '=')
		temp[i] = cmd[1][i];
	temp[i] = '\0';
	i = -1;
	while ((*env)[++i])
	{
		if (!ft_strncmp(temp, (*env)[i], ft_strlen(temp)))
			return (1);
	}
	free(temp);
	return (0);
}

//need to add case (export ARG+=10)
//une erreur ici!!!
void	modify_var_in_env(char **cmd, char ***env)
{
	char	*temp;
	int		i;
	int		j;

	j = -1;
	while (cmd[1][j] && cmd[1][j] != '=')
		j++;
	i = -1;
	while (cmd[1][j] && (*env)[++i])
	{
		if (!ft_strncmp(cmd[1], (*env)[i], j))
			break ;
	}
	temp = malloc(sizeof(char) * (ft_strlen(cmd[1]) + 1));
	if (!temp)
	{
		ft_free(*env, ft_tabsize(*env));
		exit(EXIT_FAILURE);
	}
	temp = ft_memcpy(temp, cmd[1], ft_strlen(cmd[1]));
	free((*env)[i]);
	(*env)[i] = NULL;
	(*env)[i] = temp;
}

void	create_new_var_env(char **cmd, char ***env)
{
	char	**new_env;
	char	*temp;
	char	*cmd_cpy;

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

void	no_arg(char **env)
{
	char	**new_env;
	int		i;
	int		j;
	int		k;

	i = -1;
	// printf("\n\n%d\n\n", ft_tabsize(env));
	new_env = (char **)malloc(sizeof(char *) * (ft_tabsize(env) + 1));
	if (!new_env)
	{
		ft_free(env, ft_tabsize(env));
		exit(EXIT_FAILURE);
	}
	while (++i < ft_tabsize(env))
	{
		j = 0;
		k = -1;
		if (!ft_strchr_modified(env[i], '='))
			i++;
		else
		{
			new_env[i] = (char *)malloc(sizeof(char) * (ft_strlen((env)[i]) + 3));
			if (!new_env[i])
			{
				ft_free(env, ft_tabsize(env));
				exit(EXIT_FAILURE);
			}
			// printf("i: %d segfault 1\n", i);
			while (env[i][j] && (env)[i][j] != '=')
				new_env[i][++k] = (env)[i][j++];
			// printf("i: %d segfault 2\n", i);
			new_env[i][++k] = (env)[i][j];
			new_env[i][++k] = '"';
			while (env[i][j] && j++ < (int)ft_strlen((env)[i]))
				new_env[i][++k] = (env)[i][j];
			// printf("i: %d segfault 3\n", i);
			new_env[i][k] = '"';
			new_env[i][k + 1] = '\0';
		}
	}
	new_env[i] = NULL;
	// printf("coucou lol\n");
	// printf("\n\n%d\n\n", ft_tabsize(new_env));
	ft_sort_string_tab(new_env);
	i = -1;
	while (++i < ft_tabsize(env))
			printf("declare -x %s\n", new_env[i]);
	// printf("free 1\n");
	// i = -1;
	// while (new_env[++i])
	// {
	// 	free(new_env[i]);
	// 	// new_env[i] = NULL;
	// }
	// free(new_env);
	// new_env = NULL;
	// printf("free 2\n");
	ft_free(new_env, ft_tabsize(new_env));
}

void	ft_export(char **cmd, char ***env)
{
	// static char	**temp = NULL;
	// // int		i;

	// if (!temp)
	// 	temp = cpy_env(*env);
	if (cmd[1] == NULL)
	{
		// int	i = -1;
		// while (++i < ft_tabsize(temp))
		// 	printf("%s\n", temp[i]);
		no_arg(*env);
		// i = -1;
		// while ((*env)[++i])
		// {
		// 	temp = ft_strjoin("declare -x ", (*env)[i]);
		// 	printf("%s\n", temp);
		// 	free(temp);
		// 	temp = NULL;
		// }
	}
	// else if (!ft_strchr(cmd[1], '='))
	// {
	// 	if (!check_if_already_in_env(cmd, &temp))
	// 		create_new_var_env(cmd, &temp);
	// 	return ;
	// }
	else if (check_if_already_in_env(cmd, env))
		return ;
	else if (check_if_in_env(cmd, env))
		modify_var_in_env(cmd, env);
	else
		create_new_var_env(cmd, env);
}
