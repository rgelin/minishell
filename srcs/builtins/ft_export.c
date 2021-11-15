
#include "../minishell.h"

//need to add case (export ARG+=10)
// char	*to_add(char **cmd)
// {
// 	int	i;

// 	i = -1;
// 	while ()
// }
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
	temp = ft_memcpy(temp, (*env)[i], ft_strlen((*env)[i]));
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
	// int		j;

	i = find_var_in_env(cmd, *env);
	temp = ft_strdup(cmd[1]);
	// temp = malloc(sizeof(char) * (ft_strlen(cmd[1]) + 1));
	// if (!temp)
	// {
	// 	ft_free(*env, ft_tabsize(*env));
	// 	exit(EXIT_FAILURE);
	// }
	// j = -1;
	// while (cmd[1][++j])
	// 	temp[j] = cmd[1][j];
	// temp[j] = '\0';
	// add_to_var(cmd, env);
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

char	*add_quotes(char *env_line)
{	
	int		i;
	int		j;
	char	*new_line;

	i = -1;
	j = 0;
	new_line = (char *)malloc(sizeof(char) * (ft_strlen(env_line) + 3));
	if (!new_line)
		exit(EXIT_FAILURE);
	while (env_line[++i] && env_line[i] != '=')
		new_line[i] = env_line[j++];
	new_line[i++] = env_line[j++];
	new_line[i++] = '"';
	while (env_line[j])
		new_line[i++] = env_line[j++];
	new_line[i] = '"';
	new_line[i + 1] = '\0';
	return (new_line);
}

void	no_arg(char ***env)
{
	char	**new_env;
	int		i;

	i = -1;
	// printf("tabsize: %d\n", ft_tabsize(*env));
	new_env = (char **)malloc(sizeof(char *) * (ft_tabsize(*env) + 1));
	if (!new_env)
	{
		ft_free(*env, ft_tabsize(*env));
		exit(EXIT_FAILURE);
	}
	while (++i < ft_tabsize(*env))
	{
		if (ft_strchr_modified((*env)[i], '=') == 0)
		{
			new_env[i] = ft_strdup((*env)[i]);
			if (!new_env[i])
				exit(EXIT_FAILURE);
			// printf("i: %d \x1b[32m%s\n\x1b[0m", i, new_env[i]);
		}
		else
			new_env[i] = add_quotes((*env)[i]);
		// printf("i: %d \x1b[32m%s\n\x1b[0m", i, (*env)[i]);
		// printf("i: %d \x1b[33m%s\n\x1b[0m", i, new_env[i]);
	}
	new_env[i] = NULL;
	ft_sort_string_tab(new_env);
	i = -1;
	while (new_env[++i])
			printf("declare -x %s\n", new_env[i]);
	ft_free(new_env, ft_tabsize(new_env));
}

char	*ft_trim_quotes(char *str, char c)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str)));
	if (!new_str)
		exit(EXIT_FAILURE);
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

void	ft_export(char **cmd, char ***env)
{

	if (cmd[1] == NULL)
		no_arg(env);
	else if (check_if_already_in_env(cmd, env))
		return ;
	else if (find_var_in_env(cmd, *env))
	{
		if (ft_strchr_modified(cmd[1], '='))
			modify_var_in_env(cmd, env);
	}
	else
		create_new_var_env(cmd, env);
}
