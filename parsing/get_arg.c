#include "../srcs/minishell.h"

char	**return_arg(char **tmp, int n)
{
	int		j;
	int		i;
	char	**arg;

	arg = NULL;
	j = 0;
	i = 0;
	arg = malloc(sizeof(char *) * (n + 1));
	if (!arg)
	{
		free(arg);
		return (NULL);
	}
	while (tmp[++i] != NULL)
	{
		if (*tmp[i] == '<' || *tmp[i] == '>')
			break ;
		if (*tmp[i] != '-' && *tmp[i] != '<' && *tmp[i] != '>')
		{
			arg[j] = ft_strdup(tmp[i]);
			j++;
		}
	}
	arg[j] = NULL;
	return (arg);
}

char	**get_arg(char *line)
{
	char	**arg;
	char	**tmp;
	int		i;
	int		n;

	n = 0;
	i = 1;
	tmp = ft_split_parsing(line, ' ');
	while (tmp[i] != NULL)
	{
		if (*tmp[i] == '<' || *tmp[i] == '>')
			break ;
		if (*tmp[i] != '-' && *tmp[i] != '<' && *tmp[i] != '>') 
			n++;
		i++;
	}
	arg = return_arg(tmp, n);
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return (arg);
}
