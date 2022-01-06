#include "../srcs/minishell.h"

void	return_opt(int *popt, char *line, char **options)
{
	int	i;
	int	opt;
	int	index;

	i = 0;
	opt = 0;
	while (popt[i] != -1)
	{
		index = popt[i];
		opt = index;
		while (line[opt] != '\0')
		{
			if (check_quote(line, opt)
				&& (line[opt] == ' ' || line[opt + 1] == '\0'))
			{
				options[i] = ft_substr(line, index, opt - (index - 1));
				options[i] = ft_strtrim(options[i], "- ");
				break ;
			}
			opt++;
		}
		i++;
	}
	options[i] = NULL;
}

char	**get_opt(char *line)
{
	int		i;
	int		opt;
	int		*popt;
	char	**options;

	opt = 0;
	i = -1;
	while (line[++i] != '\0')
	{
		if (check_quote(line, i) && line[i] == '-')
			opt++;
	}
	popt = get_index(line, opt, '-');
	options = malloc(sizeof(char *) * (opt + 1));
	if (!options)
	{
		free(options);
		return (NULL);
	}
	return_opt(popt, line, options);
	free(popt);
	return (options);
}
