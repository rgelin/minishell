
#include "../srcs/minishell.h"

void	init_tab(t_pars *tab)
{
	tab->command = NULL;
	tab->option = NULL;
	tab->arg = NULL;
	//tab->input = NULL;
	//tab->output = NULL;
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
	options = malloc(sizeof(char *) * (opt + 1));
	if (!options)
	{
		free(options);
		//plutot mettre en void pour pouvoir free et exit
		return (NULL);
	}
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
				options[i] = ft_strtrim(options[i], "- ");
				break ;
			}
			opt++;
		}
		i++;
	}
	options[i] = NULL;
	free(popt);
	return (options);
}

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

char **get_arg(char *line)
{
	char	**arg;
	char	**tmp;
	int		i;
	int		j;
	int		n;

	n = 0;
	i = 1;
	j = 0;
	tmp = ft_split_parsing(line, ' ');
	while (tmp[i] != NULL)
	{
		if (*tmp[i] == '<' || *tmp[i] == '>')
			break ;
		if (*tmp[i] != '-' && *tmp[i] != '<' && *tmp[i] != '>')
			n++;
		i++;
	}
	arg = NULL;
	arg = malloc(sizeof(char *) * (n + 1));
	if (!arg)
	{
		free(arg);
		//plutot mettre en void pour pouvoir free et exit
		return (NULL);
	}
	i = 1;
	while (tmp[i] != NULL)
	{
		if (*tmp[i] == '<' || *tmp[i] == '>')
			break ;
		if (*tmp[i] != '-' && *tmp[i] != '<' && *tmp[i] != '>')
		{
			arg[j] = ft_strdup(tmp[i]);
			j++;
		}
		i++;
	}
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	arg[j] = NULL;
	return (arg);
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
		tab.option = get_opt(line);
		tab.redirect = get_redirect(line, '>');
		tab.arg = get_arg(line);
	}
	else
	{
		tab.command = ft_substr(line, 0, ft_strlen(line));
		tab.command = ft_strtrim(tab.command, " ");
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
		ft_free_pars_error(s);
		write(1, "Error malloc\n", 13);
		exit(EXIT_FAILURE);
	}
	while (++i <= s->n_of_pipe)
		comd[i] = get_command(s->cm[i], s);
	free(s->line);
	return (comd);
}
