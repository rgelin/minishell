#include "../srcs/minishell.h"

int		nbr_of_heredoc(char *line)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (check_quote(line, i) && line[i] == '<' && line[i + 1] == '<')
			n++;
		i++;
	}
	return (n);
}

char *cut_heredoc(char *line, int index, char **tab_here)
{
	char	*tmp;
	char	*rest;
	char	*new_line;
	int		n;
	int		m;
	char	*nl;

	n = index;
	m = 0;
	tmp = NULL;
	nl = NULL;
	rest = NULL;
	new_line = NULL;
	tmp = ft_substr(line, 0, index);
	while (line[n] == '<')
	{
		n++;
		m++;
	}
	while (line[n] == ' ' || line[n] == '\0')
	{
		n++;
		m++;
	}
	while (ft_isascii(line[n]))
	{
		if (line[n] == ' ' || line[n] == '\0')
			break;
		n++;
		m++;
	}
	*tab_here = ft_substr(line, index + 1, m - 1);
	*tab_here = ft_strtrim(*tab_here, "< ");
	//printf("tab_here = %s\n", *tab_here);
	rest = ft_substr(line, index + m, (ft_strlen(line) - index));
	//printf("rest = %s\n", rest);
	new_line = ft_strjoin_double_free(tmp, "");
	new_line = ft_strjoin_double_free(new_line, rest);
	//free(line);
	//line = NULL;
	return (new_line);
}

char *get_heredoc(char *line, t_pars *tab_here)
{
	int		i;
	char	*new_line;
	int		nbr_of_here;
	char 	**tab;
	int		j;

	i = 0;
	j = 0;
	nbr_of_here = nbr_of_heredoc(line);
	//printf("%d\n", nbr_of_here);
	if (nbr_of_here > 0)
	{
		tab = malloc(sizeof(char *) * (nbr_of_here + 1));
		if (!tab)
			exit(EXIT_FAILURE);
	}
	else
		return (line);
	while (line[i] != '\0')
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			new_line = cut_heredoc(line, i, &tab[j]);
			//printf("tab[%d] = %s\n", j, tab[j]);
			j++;
			line = new_line;
			i = -1;
		}
		i++;
	}
	tab[j] = NULL;
	tab_here->heredoc = tab;
	new_line = ft_strtrim(new_line, " ");
	return (new_line);
}
