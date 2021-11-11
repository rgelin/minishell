
#include "minishell.h"

char **get_everything(char *line, char c)
{
	int	i;
	int	opt;
	int *popt;
	int index;
	char **options;

	opt = 0;
	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == c)
			opt++;
	}
	if (opt == 0)
		return (NULL);
	popt = get_index(line, opt, c);
	options = malloc(sizeof(char *) * opt);
	if (!options)
	{
		free(options);
		exit(EXIT_FAILURE);
	}
	i = 0;
	opt = 0;
	while (popt[i] != -1)
	{
		index = popt[i];
		opt = index;
		opt++;
		while (line[opt] !='\0')
		{
			if (check_quote(line, opt) && (line[opt] == '>' || line[opt] == '<' || line[opt] == '-' ||
				line[opt + 1] == '\0'))
			{
				options[i] = ft_substr(line, index, opt - (index - 1));
				options[i] = ft_strtrim(options[i], "<>-");
				if (c == '>')
					printf("output = %s\n", options[i]);
				if (c == '<')
					printf("input = %s\n", options[i]);
				break ;
			}
			opt++;
		}
		i++;
	}
	free(popt);
	return (options);
}
