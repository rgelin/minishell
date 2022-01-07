#include "../srcs/minishell.h"

int	nbr_of_heredoc(char *line)
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

void	count_char(t_tmp *tmp, char *line)
{
	while (line[tmp->n] == '<')
	{
		tmp->n++;
		tmp->m++;
	}
	while (line[tmp->n] == ' ' || line[tmp->n] == '\0')
	{
		tmp->n++;
		tmp->m++;
	}
	while (ft_isascii(line[tmp->n]))
	{
		if (line[tmp->n] == ' ' || line[tmp->n] == '\0')
			break ;
		tmp->n++;
		tmp->m++;
	}	
}

char	*cut_heredoc(char *line, int index, char **tab_here)
{
	t_tmp	tmp;

	init_tmp(&tmp);
	tmp.n = index;
	tmp.tmp = ft_substr(line, 0, index);
	count_char(&tmp, line);
	*tab_here = ft_substr(line, index + 1, tmp.m - 1);
	*tab_here = ft_strtrim(*tab_here, "< ");
	tmp.rest = ft_substr(line, index + tmp.m, (ft_strlen(line) - index));
	tmp.new_line = ft_strjoin_double_free(tmp.tmp, "");
	tmp.new_line = ft_strjoin_double_free(tmp.new_line, tmp.rest);
	//free(line);
	//line = NULL;
	return (tmp.new_line);
}

char	*get_tab_heredoc(char *line, char **tab)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			new_line = cut_heredoc(line, i, &tab[j]);
			j++;
			line = new_line;
			i = -1;
		}
		i++;
	}
	tab[j] = NULL;
	return (new_line);
}

char	*get_heredoc(char *line, t_pars *tab_here)
{
	char	*new_line;
	int		nbr_of_here;
	char	**tab;

	new_line = NULL;
	tab = NULL;
	nbr_of_here = nbr_of_heredoc(line);
	if (nbr_of_here < 1)
		return (line);
	tab = malloc(sizeof(char *) * (nbr_of_here + 1));
	if (!tab)
		exit(EXIT_FAILURE);
	new_line = get_tab_heredoc(line, tab);
	tab_here->heredoc = tab;
	new_line = ft_strtrim(new_line, " ");
	return (new_line);
}
