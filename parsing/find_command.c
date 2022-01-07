#include "../srcs/minishell.h"

void	init_tab(t_pars *tab)
{
	tab->command = NULL;
	tab->option = NULL;
	tab->arg = NULL;
	//tab->input = NULL;
	//tab->output = NULL;
	tab->heredoc = NULL;
	tab->next_char = NULL;
	tab->redirect = NULL;
}

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

t_pars	get_command(char *line, t_state *s)
{
	int		next;
	t_pars	tab;
	char	*new_line;

	(void)s;
	init_tab(&tab);
	new_line = get_heredoc(line, &tab);
	//printf("new_line = %s\n", new_line);
	if (ft_get_index(new_line) != 0)
	{
		next = ft_get_index(new_line);
		tab.command = ft_substr(new_line, 0, next);
		tab.command = ft_strtrim(tab.command, " ");
		tab.option = get_opt(new_line);
		tab.redirect = get_redirect(new_line);
		tab.arg = get_arg(new_line);
	}
	else
	{
		tab.command = ft_substr(new_line, 0, ft_strlen(new_line));
		tab.command = ft_strtrim(tab.command, " ");
	}
	return (tab);
}

/*
t_pars	get_command(char *line, t_state *s)
{
	int		next;
	t_pars	tab;
	//char	*new_line;

	(void)s;
	init_tab(&tab);
	//new_line = get_heredoc(line, &tab);
	//new_line = ft_strtrim(new_line, " ");
	//printf("new_line = %s\n", new_line);
	if (ft_get_index(line) != 0)
	{
		next = ft_get_index(line);
		tab.command = ft_substr(line, 0, next);
		tab.command = ft_strtrim(tab.command, " ");
		tab.option = get_opt(line);
		tab.redirect = get_redirect(line);
		tab.arg = get_arg(line);
	}
	else
	{
		tab.command = ft_substr(line, 0, ft_strlen(line));
		tab.command = ft_strtrim(tab.command, " ");
	}
	return (tab);
}*/
//fonction où on recoit chaque ligne divisé par des pipes

t_pars	*find_command(t_state *s)
{
	int		i;
	t_pars	*comd;

	i = -1;
	comd = malloc(sizeof(t_pars) * (s->n_of_pipe + 1));
	if (!comd)
	{
		free(comd);
		ft_free_pars_error(s);
		write(1, "Error malloc\n", 13);
		exit(EXIT_FAILURE);
	}
	while (++i <= s->n_of_pipe)
		comd[i] = get_command(s->cm[i], s);
	//free(s->line);
	return (comd);
}
