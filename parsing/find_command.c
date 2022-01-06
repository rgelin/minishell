#include "../srcs/minishell.h"

void	init_tab(t_pars *tab)
{
	tab->command = NULL;
	tab->option = NULL;
	tab->arg = NULL;
	//tab->input = NULL;
	//tab->output = NULL;
	tab->next_char = NULL;
	tab->redirect = NULL;
}
//je reprendre tout mais pas vraiment clean
/*
t_pars	get_command(char *line, t_state *s)
{
	int		next;
	t_pars	tab;

	(void)s;
	init_tab(&tab);
	if (ft_get_index(line) != 0)
	{
		printf("ici\n");
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

t_pars	get_command(char *line, t_state *s)
{
	int		next;
	t_pars	tab;

	(void)s;
	init_tab(&tab);
	next = ft_get_index(line);
	tab.command = ft_substr(line, 0, next);
	tab.command = ft_strtrim(tab.command, " ");
	tab.option = get_opt(line);
	tab.redirect = get_redirect(line);
	tab.arg = get_arg(line);
	return (tab);
}

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
	free(s->line);
	return (comd);
}
