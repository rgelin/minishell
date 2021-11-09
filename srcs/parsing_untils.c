
#include "minishell.h"

int	ft_get_index(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
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
