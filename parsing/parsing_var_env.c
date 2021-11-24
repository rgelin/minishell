
#include "../srcs/minishell.h"

extern int	g_exit_code;

char	*insert_exit_code(char *line, int index)
{
	char	*code;
	char	*tmp_line;
	char	*rest;
	char	*new_line;

	code = ft_itoa(g_exit_code);
	tmp_line = ft_substr(line, 0, index);
	rest = ft_substr(line, index + 2, (ft_strlen(line) - index));
	new_line = ft_strjoin(tmp_line, code);
	free(code);
	new_line = ft_strjoin(new_line, rest);
	free(rest);
	free(line);
	return (new_line);
}

char	*insert_var_env(char *line, int index)
{
	char	*tmp;
	char	*rest;
	char	*new_line;
	char	*var;
	int		n;
	int		m;
	
	n = index;
	m = 0;
	tmp = ft_substr(line, 0, index);
	//printf("%s\n", tmp);
	new_line = NULL;
	while(line[n] != '\0')
	{
		if (line[n] == ' ' || line[n] == '\0')
			break;
		n++;
		m++;
	}
	//printf("%s\n", ft_substr(line, index + 1, m));
	var = getenv(ft_substr(line , index + 1, m - 1));
	//printf("var = %s\n", var);
	rest = ft_substr(line, index + m, (ft_strlen(line) - index));
	//printf("rest = %s\n", rest);
	new_line = ft_strjoin(tmp, var);
	//free(var);
	new_line = ft_strjoin(new_line, rest);
	free(rest);
	free(line);
	return (new_line);
}

char	*check_var_env(char *line)
{
	int		i;
	char	*new_line;

	i = 0;
	
	while (line[i] != '\0')
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			new_line = insert_exit_code(line, i);
			line = new_line;
		}
		else if (line[i] == '$')
		{
			new_line = insert_var_env(line, i);
			line = new_line;
		}
		i++;
	}
	return (new_line);
}

char	*check_var_env_bis(char *line)
{
	int		i;
	char	*new_line;

	i = 0;
	if (line[i] == '$' && line[i + 1] == '?')
	{
		new_line = ft_itoa(g_exit_code);
		free(line);
	}
	else if (line[i] == '$')
	{
		new_line = getenv(ft_strtrim(line, "$"));
		//free(line);
	}
	else
		new_line = line;
	return (new_line);
}

char	**ft_arg(char **arg)
{
	int	i;
	
	i = 0;
	while (arg && arg[i])
	{
		if (arg[i][0] == '\'')
		{
			arg[i] = ft_strtrim(arg[i], "\'");
		}
		else if (arg[i][0] == '\"')
		{
			arg[i] = ft_strtrim(arg[i], "\"");
			//printf("before : %s\n", arg[i]);
			arg[i] = check_var_env(arg[i]);
			//printf("after : %s\n", arg[i]);
		}
		else
		{
			//printf("before : %s\n", arg[i]);
			arg[i] = check_var_env_bis(arg[i]);
			//printf("after : %s\n", arg[i]);
		}
		i++;
	}
	return (arg);
}
