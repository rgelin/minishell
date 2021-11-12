
#include "minishell.h"

void	init_tab(t_pars *tab)
{
	tab->command = NULL;
	tab->option = NULL;
	tab->arg = NULL;
	tab->input = NULL;
	tab->output = NULL;
	tab->next_char = NULL;
}

int	ft_get_index_opt(char *s, char c, int i)
{
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}
//pour avoir les options. regarder pour enlever et mettre get_everything
char **get_opt(char *line)
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
		if (line[i] == '-')
			opt++;
	}
	popt = get_index(line, opt, '-');
	options = malloc(sizeof(char *) * opt);
	i = 0;
	opt = 0;
	while (popt[i] != -1)
	{
		index = popt[i];
		opt = index;
		while (line[opt] !='\0')
		{
			if (check_quote(line, opt) && (line[opt] == ' ' || line[opt + 1] == '\0'))
			{
				options[i] = ft_substr(line, index, opt - (index - 1));
				options[i] = ft_strtrim(options[i], "-");
				printf("opt = %s\n", options[i]);
				break ;
			}
			opt++;
		}
		i++;
	}
	free(popt);
	return (options);
}
/*
char *get_arg(char *line)
{
	int		i;
	char	*s;

	s = NULL;
	i = ft_strlen(line);
	while (line[i] != ' ' && i != 0)
	{
		if (line[i] == '-')
			return (s);
		i--;
	}
	s = ft_substr(line, i, ft_strlen(line));
	s = ft_strtrim(s, " ");
	//printf("arg = %s\n", s);
	return (s);
}
*/

int	check_number_char(char *line, char c)
{
	int	i;
	int	n;
	int	total;

	total = 0;
	i = -1;
	n = 0;
	while (line[++i] != '\0')
	{
		if (line[i] == c && check_quote(line, i))
			n++;
	}
	total = n % 2;
	if (total == 0)
		return n;
	return (0);
}

char	**get_arg(char *line, t_state *s)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	s->n_of_sq = check_number_char(line, '\'');
	s->n_of_dq = check_number_char(line, '"');
	if (s->n_of_sq != 0)
		s->sq = get_index(line, s->n_of_sq, '\'');
	if (s->n_of_dq != 0)
		s->dq = get_index(line, s->n_of_dq, '"');
	while (s->sq[i] > -1 || s->dq[j] > -1)
	{
		if (s->sq[i] > s)
	}
}

//je reprendre tout mais pas vraiment clean
t_pars	get_command(char *line, t_state *s)
{
	int		next;
	t_pars	tab;

	(void)s;
	init_tab(&tab);
	if (ft_get_index(line) != 0)
	{
		next = ft_get_index(line);
		tab.command = ft_substr(line, 0, next);
		tab.command = ft_strtrim(tab.command, " ");
		printf("-command = %s\n", tab.command);
		tab.option = get_opt(line);
		//tab.arg = get_arg(line);
		tab.input = get_everything(line, '>');
		tab.output = get_everything(line, '<');
	}
	else
	{
		tab.command = ft_substr(line, 0, ft_strlen(line));
		tab.command = ft_strtrim(tab.command, " ");
		//printf("*command = %s\n", tab.command);
	}
	return (tab);
}

t_pars *find_command(t_state *s)
{
	int		i;
	t_pars	*comd;

	i = -1;
	comd = malloc(sizeof(t_pars) * (s->n_of_pipe + 1));
	if (!comd)
	{
		free(comd);
		ft_free_pars_tab(s);
		exit(EXIT_FAILURE);
	}
	while (++i <= s->n_of_pipe)
		comd[i] = get_command(s->cm[i], s);
	return (comd);
}
