
#include "../minishell.h"

// need to add case (export ARG+=10)
char	*to_add(char *str)
{
	int		i;
	int		j;
	int		count;
	char	*res;

	i = ft_strlen(str);
	count = 0;
	while (str[--i] != '=')
		count++;
	res = ft_calloc(sizeof(char), (size_t)(count + 1));
	if (!res)
		exit(EXIT_FAILURE);
	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	j = 0;
	while (str[i])
		res[j++] = str[i++];
	res[j] = '\0';
	return (res);
}

void	modify_var_in_env(char **cmd, char ***env)
{
	char	*temp;
	int		i;

	i = find_var_in_env(cmd, *env);
	if (ft_strchr_modified(cmd[1], '+'))
		temp = ft_strdup(ft_strcat((*env)[i], to_add(cmd[1])));
	else
		temp = ft_strdup(cmd[1]);
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
	new_env = (char **)malloc(sizeof(char *) * (ft_tabsize(*env) + 1));
	if (!new_env)
		exit(EXIT_FAILURE);
	while (++i < ft_tabsize(*env))
	{
		if (ft_strchr_modified((*env)[i], '=') == 0)
		{
			new_env[i] = ft_strdup((*env)[i]);
			if (!new_env[i])
				exit(EXIT_FAILURE);
		}
		else
			new_env[i] = add_quotes((*env)[i]);
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
