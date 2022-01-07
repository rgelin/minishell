#include "../srcs/minishell.h"

int	ft_get_index(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ' || s[i] == '<' || s[i] == '>')
			return (i);
		i++;
	}
	return (0);
}

void	init_tmp(t_tmp *tmp)
{
	tmp->tmp = NULL;
	tmp->rest = NULL;
	tmp->new_line = NULL;
	tmp->n = 0;
	tmp->m = 0;
	tmp->nl = NULL;
	tmp->var = NULL;
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
			p_tab[j++] = i;
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
	while (test && test[++index] != NULL)
		free(test[index]);
	if (test != NULL)
		free(test);
	free(line);
	return (tmp);
}
