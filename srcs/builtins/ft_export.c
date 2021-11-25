
#include "../minishell.h"

// need to add case (export ARG+=10)
extern int	g_exit_code;

void	create_new_var_env(char *arg, char ***env)
{
	char	**new_env;
	char	*temp;
	char	*cmd_cpy;

	new_env = ft_realloc_env(env, 2);
	cmd_cpy = ft_strtrim_modified(arg, "+");
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

static char	*parse_arg(char *arg)
{
	char *res;
	int	i;

	res = ft_strtrim_modified(arg, "\""); //leak
	free(arg);
	arg = NULL;
	i = -1;
	while (res[++i] && res[i] != '=')
	{
		if (res[i] == '+' && res[i + 1] == '=')
			break ;
		else if (!ft_isalpha(res[0]) || !ft_isalnum(res[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", res);
			g_exit_code = 1;
			return (NULL);
		}
	}
	return (res);
}

/*-------exit code---------
	* ARG must begin by a letter
	* ARG name can't contain only letters and numbers
		(!! ARG+=8 is ok but AR+G+=8 not ok --> + and = must follow each other)
	* exit message: "export: `A.8': not a valid identifier"
	* exit code = 1 
	* Make a check error of ARG (ex: export +=9)
*/
void	ft_export(t_exc exc, char ***env)
{
	int	i;

	g_exit_code = 0;
	i = 0;
	if (exc.arg == NULL)
		no_arg(env);
	else
	{
		while (exc.arg[i])
		{
			exc.arg[i] = parse_arg(exc.arg[i]);
			if (!exc.arg[i])
				i++;
			else if (check_if_already_in_env(exc.arg[i], env))
				i++;
			else if (find_var_in_env(exc.arg[i], *env) != -1)
			{
				if (ft_strchr_modified(exc.arg[i], '='))
					modify_var_in_env(exc.arg[i], env);
				i++;
			}
			else
				create_new_var_env(exc.arg[i++], env);
		}

	}
}
