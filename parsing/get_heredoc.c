#include "../srcs/minishell.h"

int		nbr_of_heredoc(char *line)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (check_quote(line, i) && line[i] == '>' && line[i] == '>')
			n++;
		i++;
	}
	return (n);
}

char	*cut_heredoc(char *line, int index, char **tab_here)
{
	char	*tmp;
	char	*rest;
	char	*new_line;
	//char	*var;
	int		n;
	int		m;
	char	*nl;

	n = index;
	m = 0;
	tmp = NULL;
	var = NULL;
	nl = NULL;
	rest = NULL;
	new_line = NULL;
	tmp = ft_substr(line, 0, index);
	while (line[n] == '>')
	{
		n++;
		m++;
	}
	while (line[n] == ' ' || line[n] == '\0')
	{
		n++;
		m++;
	}
	while (line[n] != ' ' || line[n] == '\0')
	{
		n++;
		m++;
	}
	nl = ft_substr(line, index + 1, m - 1);
	printf("nl = %s\n", nl);
	//var = our_getenv(ft_strtrim(nl, "$"), env);
	rest = ft_substr(line, index + m, (ft_strlen(line) - index));
	new_line = ft_strjoin_double_free(tmp, var);
	new_line = ft_strjoin_double_free(new_line, rest);
	free(line);
	line = NULL;
	return (new_line);
}

char	*get_heredoc(char *line, t_pars *tab_here)
{
	int		i;
	char	*new_line;
	int		nbr_of_here;

	i = 0;
	nbr_of_here = nbr_of_heredoc(line);
	if (nbr_of_here > 0)
	{
		tab_here->heredoc = malloc(sizeof(char *) * (nbr_of_here + 1);
		if (!tab_here->heredoc)
			exit(EXIT_FAILURE);
	}
	else
		return (line);
	while (line[i] != '\0')
	{
		if (line[i] == '>' && line[i + 1] == '>')
		{
			new_line = cut_heredoc(line, i, tab_here->heredoc++);
			line = new_line;
			i = -1;
		}
		i++;
	}
	tab_here->heredoc = NULL;
	return (new_line);
}
