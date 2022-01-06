
#include "../minishell.h"

char	*ft_strtrim_plus_equal(char *arg)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)malloc(sizeof(char) * ft_strlen(arg));
	if (!str)
		exit(EXIT_FAILURE);
	i = -1;
	j = 0;
	while (arg && arg[++i] && arg[i] != '=')
	{
		if (!(arg[i] == '+' && arg[i + 1] == '='))
			str[j++] = arg[i];
	}
	str[j++] = '=';
	while (arg && arg[++i])
			str[j++] = arg[i];
	str[j] = '\0';
	return (str);
}

void	create_new_var_env(char *arg, char ***env)
{
	char	**new_env;
	char	*temp;
	char	*cmd_cpy;

	new_env = ft_realloc_env(env, 2);
	if (ft_strchr(arg, '+'))
		cmd_cpy = ft_strtrim_plus_equal(arg);
	else
		cmd_cpy = ft_strdup(arg);
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
	while ((*env)[++i])
	{
		if (ft_strchr_modified((*env)[i], '=') == 0)
		{
			new_env[i] = ft_strdup((*env)[i]);
		}
		else
			new_env[i] = add_quotes((*env)[i]);
	}
	new_env[i] = NULL;
	ft_sort_string_tab(new_env);
	i = -1;
	while (new_env && new_env[++i])
			printf("declare -x %s\n", new_env[i]);
	ft_free(new_env, ft_tabsize(new_env));
}

static char	*parse_arg(char *arg)
{
	char *res;
	int	i;

	res = ft_strtrim_modified(arg, "\""); //leak
	free(arg);
	arg = NULL;
	i = -1;
	if (!ft_isalpha(res[0]))
	{
		ft_perror("export", res, "not a valid identifier");
		g_global.exit_code = 1;
		return (NULL);
	}
	while (res[++i] && res[i + 1] != '=')
	{
		if (res[i] == '+' && res[i + 1] == '=')
			break ;
		else if (!ft_isalnum(res[i]) && res[i] != '_')
		{
			ft_perror("export", res, "not a valid identifier");
			g_global.exit_code = 1;
			return (NULL);
		}
	}
	return (res);
}

void	ft_export(t_exc exc, char ***env)
{
	int	i;

	i = 0;
	g_global.exit_code = 0;
	if (!exc.arg)
		no_arg(env);
	else
	{
		while (exc.arg[i])
		{
			exc.arg[i] = parse_arg(exc.arg[i]);
			if (exc.arg[i] && !check_if_already_in_env(exc.arg[i], env))
			{
				if (find_var_in_env(exc.arg[i], *env) != -1)
				{
					if (ft_strchr_modified(exc.arg[i], '='))
						modify_var_in_env(exc.arg[i], env);
				}
				else
					create_new_var_env(exc.arg[i], env);
			}
			i++;
		}

	}
}
