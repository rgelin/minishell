#include "../srcs/minishell.h"

int	ft_get_index(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '-' || s[i] == ' ' || s[i] == '<' || s[i] == '>')
			return (i);
		i++;
	}
	return (0);
}

int	ft_test(char *line)
{
	int	x;

	x = ft_strlen(line);
	while (line[x] != ' ' && x != 0)
		x--;
	if (x != 0)
		return (x);
	x--;
	return (0);
}

int	*get_index(char *line, size_t size, char c)
{
	int	i;
	int	j;
	int	*p_tab;

	j = 0;
	i = 0;
	p_tab = 0;
	p_tab = malloc(sizeof(int *) * (size + 1));
	if (!p_tab)
	{
		free (p_tab);
		return (0);
	}
	while (line[i] != '\0')
	{
		if (c == '-' && line[i] == '-' && line[i -1] != ' ')
			i++;
		if (line[i] == c && check_quote(line, i))
		{
			p_tab[j] = i;
			j++;
		}
		i++;
	}
	p_tab[j] = -1;
	return (p_tab);
}

char	*our_getenv(char *line, char **env)
{
	int		index;
	char	*var;
	char	*tmp;
	char	**test;

	var = NULL;
	test = NULL;
	index = find_var_in_env(line, env);
	if (index >= 0)
	{
		var = env[index];
		test = ft_split(var, '=');
		tmp = ft_strdup(test[1]);
	}
	if (index == -1)
		tmp = "";
	index = -1;
	while(test && test[++index] != NULL)
		free(test[index]);
	if (test != NULL)
		free(test);
	free(line);
	return (tmp);
}
