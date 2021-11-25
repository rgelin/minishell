
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

static char *get_to_find(char *arg)
{
	char	*to_find;
	int i;
	int j;
	i = 0;
	j = 0;
	to_find = ft_calloc(sizeof(char), ft_strlen(arg));
	if (!to_find)
		exit(EXIT_FAILURE);
	while (arg[j] && arg[j] != '=')
	{
		if (arg[i] == '+')
			j++;
		else
			to_find[i++] = arg[j++];
	}
	// if (to_find[i] != '=')
	//  to_find[i++] = '=';
	to_find[i] = '\0';
	return (to_find);
}
int find_var_in_env(char *arg, char **env)
{
	char    *to_find;
	int i;
	int j;
	(void)env;
	// i = 0;
	// j = 0;
	// to_find = ft_calloc(sizeof(char), ft_strlen(arg));
	// if (!to_find)
	//  exit(EXIT_FAILURE);
	// while (arg[j] && arg[j] != '=')
	// {
	//  if (arg[i] == '+')
	//      j++;
	//  else
	//      to_find[i++] = arg[j++];
	// }
	// if (to_find[i] != '=')
	//  to_find[i++] = '=';
	// to_find[i] = '\0';
	to_find = get_to_find(arg);
	// printf("%s\n", to_find);
	i = -1;
	j = 0;
	// printf("len: %d\n", (int)ft_strlen(to_find));
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		// printf("j: %d || %c\n", j, env[i][j]);
		if (!ft_strncmp(env[i], to_find, j) && ((int)ft_strlen(to_find) == j))
		{
			// printf("index: %d\n", i);
			return (i);
		}
	}
	free(to_find);
	to_find = NULL;
	return (-1); //changer les conditions par rapport a ca
}

// int	find_var_in_env(char *arg, char **env)
// {
// 	char	*to_find;
// 	int	i;
// 	int j;

// 	i = -1;
// 	j = 0;
// 	to_find = ft_strtrim_modified(arg, "+");
// 	if (!to_find)
// 		exit(EXIT_FAILURE);
// 	while (to_find[j] && to_find[j] != '=')
// 		j++;;
// 	i = -1;
// 	while (env[++i])
// 	{
// 		if (!ft_strncmp(env[i], to_find, j))
// 			return (i);
// 	}
// 	free(to_find);
// 	to_find = NULL;
// 	return (-1); //changer les conditions par rapport a ca
// }

//we check if the exact same argument already exist in env (add +1 strncmp in of just "ARG=")
int		check_if_already_in_env(char *arg, char ***env)
{
	int i;

	i = -1;
	// printf("strlen: %d\n", (int)ft_strlen(cmd[1]));
	while (arg && (*env)[++i])
	{
		if (!ft_strncmp(arg, (*env)[i], ft_strlen(arg) + 1))
			return (1);
	}
	return (0);
}

char	*ft_to_add(char *str)
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

void	modify_var_in_env(char *arg, char ***env)
{
	char	*temp;
	char	*to_add;
	int		i;

	i = find_var_in_env(arg, *env);
	if (ft_strchr_modified(arg, '+'))
	{
		to_add = ft_to_add(arg);
		if (ft_strchr_modified((*env)[i], '='))
			temp = ft_strjoin((*env)[i], to_add);
		else
		{
			temp = ft_strjoin((*env)[i], "=");
			temp = ft_strjoin_free(temp, to_add);
		}
		free(to_add);
		to_add = NULL;
	}
	else
		temp = ft_strdup(arg);
	free((*env)[i]);
	(*env)[i] = NULL;
	(*env)[i] = temp;
}
