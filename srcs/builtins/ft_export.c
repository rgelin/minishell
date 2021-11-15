
#include "../minishell.h"

//we check if we already have the argument as enviroment variable
int		check_if_in_env(char **cmd, char ***env)
{
	char	*temp;
	int		i;

	i = -1;
	temp = malloc(sizeof(char) * (ft_strlen(cmd[1]) + 1));
	if (!temp)
	{
		ft_free(*env, ft_tabsize(*env));
		exit(EXIT_FAILURE);
	}
	while (cmd[1][++i] && (cmd[1][i] != '=' && cmd[1][i] != '+'))
		temp[i] = cmd[1][i];
	temp[i] = '\0';
	i = -1;
	while ((*env)[++i])
	{
		if (!ft_strncmp(temp, (*env)[i], ft_strlen(temp)))
			return (1);
	}
	free(temp);
	temp = NULL;
	return (0);
}
//need to add case (export ARG+=10)
void	add_to_var(char **cmd, char ***env)
{
	char	*temp;
	int		count;
	int		i;
	int		j;

	//on check la taille du nombre a ajouter
	i = ft_strlen(cmd[1]);
	count = 0;
	while (cmd[1][--i] != '=')
		count++;
	temp = malloc(sizeof(char) * (ft_strlen(cmd[1]) + count));
	if (!temp)
	{
		ft_free(*env, ft_tabsize(*env));
		exit(EXIT_FAILURE);
	}

	//on check l'indice de la variable a modifier
	i = find_var_in_env(cmd, (*env));
	printf("env: %s\n", (*env)[i]);
	temp = (*env)[i];
	j = 0;
	while (cmd[1][j] != '=')
		j++;
	// while (cmd[1][j])
	// 	temp[ft_strlen((*env)[i] - 1 )];




}

//une erreur ici!!!
void	modify_var_in_env(char **cmd, char ***env)
{
	char	*temp;
	int		i;
	int		j;

	j = 0;
	while (cmd[1][j] && cmd[1][j] != '=')
		j++;
	i = -1;
	while ((*env)[++i])
	{
		if (!ft_strncmp(cmd[1], (*env)[i], j))
			break ;
	}
	j = find_var_in_env(cmd, *env);
	printf("j: %d\n", j);
	temp = malloc(sizeof(char) * (ft_strlen(cmd[1]) + 1));
	if (!temp)
	{
		ft_free(*env, ft_tabsize(*env));
		exit(EXIT_FAILURE);
	}
	j = -1;
	while (cmd[1][++j])
		temp[j] = cmd[1][j];
	temp[j] = '\0';
	add_to_var(cmd, env);
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

void	add_quotes(char **new_line, char *env_line)
{	
	int i;

	i = -1;
	printf("i: %d segfault 1\n", i);
	while (env_line[++i] && env_line[i] != '=')
		(*new_line)[i] = env_line[i];
	printf("c: %c\n", env_line[i]);
	printf("i: %d segfault 2\n", i);
	(*new_line)[i] = env_line[i];
	i++;
	(*new_line)[i++] = '"';
	while (env_line[++i])
		(*new_line)[i] = env_line[i];
	printf("i: %d segfault 3\n", i);
	(*new_line)[i] = '"';
	(*new_line)[i + 1] = '\0';
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
	while (env[++i])
	{
		j = 0;
		k = -1;
		new_env[i] = (char *)malloc(sizeof(char) * (ft_strlen((env)[i]) + 3));
		if (!new_env[i])
		{
			ft_free(env, ft_tabsize(env));
			exit(EXIT_FAILURE);
		}
		if (!ft_strchr_modified(env[i], '='))
		{
			while (env[i][++k])
				new_env[i][k] = env[i][k];
			new_env[i][k] = '\0';
			i++;
		}
		else
		{
			add_quotes((&new_env)[i], env[i]);
		// 	// printf("i: %d segfault 1\n", i);
		// 	while (env[i][j] && (env)[i][j] != '=')
		// 		new_env[i][++k] = (env)[i][j++];
		// 	// printf("i: %d segfault 2\n", i);
		// 	new_env[i][++k] = (env)[i][j];
		// 	new_env[i][++k] = '"';
		// 	while (env[i][j] && j++ < (int)ft_strlen((env)[i]))
		// 		new_env[i][++k] = (env)[i][j];
		// 	// printf("i: %d segfault 3\n", i);
		// 	new_env[i][k] = '"';
		// 	new_env[i][k + 1] = '\0';
		}
	}
	new_env[i] = NULL;
	ft_sort_string_tab(new_env);
	i = -1;
	while (++i < ft_tabsize(env))
			printf("declare -x %s\n", new_env[i]);
	ft_free(new_env, ft_tabsize(new_env));
}

void	ft_export(char **cmd, char ***env)
{
	if (cmd[1] == NULL)
		no_arg(*env);
	else if (check_if_already_in_env(cmd, env))
		return ;
	else if (check_if_in_env(cmd, env))
	{
		if (ft_strchr_modified(cmd[1], '='))
			modify_var_in_env(cmd, env);
	}
	else
		create_new_var_env(cmd, env);
}
