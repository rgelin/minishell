
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

//recup seulement l argument si il y a pas option
int		ft_test(char *line)
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

int		ft_check_space(char *line)
{
	int i;

	i = ft_strlen(line);
	while (i > 0)
	{
		if (line[i] == ' ')
			return (1);
		i--;
	}
	return (0);
}
//renvoie un tableau avec les index du char
int	*get_index(char *line, size_t size, char c)
{
	int	i;
	int	j;
	int *p_tab;

	j = 0;
	i = 0;
	p_tab = malloc(sizeof(int*) * (size + 1));
	if (!p_tab)
	{
		free(p_tab);
		return (0);
	}
	while (line[i] != '\0')
	{
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

int	check_redirection(char *line)
{
	int	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '>' || line[i] == '<')
			return (1);
	}
	return (0);
}
