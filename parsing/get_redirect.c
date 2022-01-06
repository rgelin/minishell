#include "../srcs/minishell.h"

int	*get_index_redirect(char *line, size_t size)
{
	int	i;
	int	j;
	int	*p_tab;

	j = 0;
	i = -1;
	p_tab = malloc(sizeof(int *) * (size + 1));
	if (!p_tab)
	{
		free(p_tab);
		return (0);
	}
	while (line[++i] != '\0')
	{
		if (((line[i] == '<' && line[i + 1] == '<')
				|| (line[i] == '>' && line[i + 1] == '>'))
			&& check_quote(line, i))
			p_tab[j++] = i++;
		else if ((line[i] == '<' || line[i] == '>') && check_quote(line, i))
			p_tab[j++] = i;
	}
	p_tab[j] = -1;
	return (p_tab);
}

char	**get_redirect_tab(char *line, int n)
{
	int		i;
	int		start;
	int		end;
	char	**tab;
	int		*index_tab;

	i = 0;
	tab = NULL;
	index_tab = NULL;
	end = 0;
	tab = malloc(sizeof(char *) * (n + 1));
	if (!tab)
		exit(EXIT_FAILURE);
	index_tab = get_index_redirect(line, n);
	while (index_tab[i] != -1)
	{
		start = index_tab[i];
		end = index_tab[i + 1];
		tab[i] = ft_substr(line, start, end - start);
		tab[i] = ft_strtrim(tab[i], " ");
		printf("tab :%s\n", tab[i]);
		//tab[i] = ft_strtrim_modified(tab[i], " ");
		//printf("%s\n", tab[i]);
		i++;
	}
	tab[i] = NULL;
	free(index_tab);
	//free(line);
	return (tab);
}

char	**get_redirect(char *line)
{
	int		i;
	char	**tab;
	int		n;

	n = 0;
	i = 0;
	tab = NULL;
	while (line[i] != '\0')
	{
		if (((line[i] == '<' && line[i + 1] == '<')
				|| (line[i] == '>' && line[i + 1] == '>'))
			&& check_quote(line, i))
		{
			n++;
			i++;
		}
		else if ((line[i] == '<' || line[i] == '>') && check_quote(line, i))
			n++;
		i++;
	}
	tab = get_redirect_tab(line, n);
	return (tab);
}
