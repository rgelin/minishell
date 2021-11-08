
#include "minishell.h"

void	init_tab(t_pars *tab)
{
	tab->command = NULL;
	tab->option = NULL;
	tab->arg = NULL;
	tab->input = NULL;
	tab->output = NULL;
	tab->rdirect = NULL;
	tab->next_char = NULL;
}

int	ft_get_index(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}
/*
char	get_option(char *s)
{

}
*/
//recup seulement l argument si il y a pas option
int		ft_test(char *line)
{
	int	x;

	x = ft_strlen(line);
	while (line[x] != ' ' && x != 0)
		x--;
	if (x != 0)
		return (x);
	x--;
	return (0);
}
int		ft_check_space(char *line)
{
	int i;

	i = ft_strlen(line);
	while (i > 0)
	{
		if (line[i] == ' ')
			return (1);
		i--;
	}
	return (0);
}

/*
char 	get_arg(char *s)
{

}
*/
t_pars	get_command(char *line, t_state *s)
{
	int		next;
	t_pars	tab;

	(void)s;
	init_tab(&tab);
	next = ft_get_index(line, '-');
	if (next != 0)
	{
		tab.command = ft_substr(line, 0, next);
		tab.command = ft_strtrim(tab.command, " ");
		printf("ma str avec opt=%s\n", tab.command);
	}
	else
	{
		if (ft_check_space(line))
		{
			next = ft_test(line);
			tab.command = ft_substr(line, 0, next);
			tab.command = ft_strtrim(tab.command, " ");
			printf("ma str sans opt =%s\n", tab.command);
		}
		else
		{
			tab.command = ft_substr(line, 0, ft_strlen(line));
			tab.command = ft_strtrim(tab.command, " ");
			printf("q une commande =%s\n", tab.command);
		}
	}
	return (tab);
}

void	find_command(t_state *s)
{
	int		i;
	t_pars	*comd;

	i = 0;
	comd = malloc(sizeof(t_pars) * (s->n_of_pipe + 1));
	if (!comd)
	{
		free(comd);
		//fonction free
		//return (0);
	}
	while (i <= s->n_of_pipe)
	{
		comd[i] = get_command(s->cm[i], s);
		//printf("%s\n", comd[i].command);
		i++;
	}
	//return (1);
}
