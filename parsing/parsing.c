#include "../srcs/minishell.h"

int	check_parsing(t_state *s)
{
	if (!check_quote(s->line, s->eof))
	{
		write(1, "Error quote\n", 12);
		ft_free_pars_error(s);
		exit(EXIT_FAILURE);
	}
	if (s->n_of_pipe >= 0)
		s->pipe = get_index(s->line, (s->n_of_pipe + 1), '|');
	return (1);
}

int	check_quote(char *line, int index)
{
	int	i;
	int	simple_quote;
	int	double_quote;

	simple_quote = 0;
	double_quote = 0;
	i = -1;
	while (++i < index)
	{
		if (line[i] == '\'')
		{
			if (simple_quote == 0 && double_quote == 0)
				simple_quote = 1;
			else
				simple_quote = 0;
		}
		if (line[i] == '"')
		{
			if (double_quote == 0 && simple_quote == 0)
				double_quote = 1;
			else
				double_quote = 0;
		}		
	}
	if (simple_quote == 0 && double_quote == 0)
		return (1);
	return (0);
}

void check_char(t_state *s)
{
	int	i;

	i = -1;
	while (s->line[++i] != '\0')
	{	
		if (s->line[i] == 124 && check_quote(s->line, i))
			s->n_of_pipe++;
	}
	s->eof = i;
}

t_pars	*parsing(t_state *s)
{
	t_pars	*tab;

	tab = NULL;
	check_char(s);
	if (check_parsing(s))
	{
		tab = split_line(s);
	}
	tab->pipe = s->n_of_pipe;
	ft_free_pars_tab(s);
	return (tab);
}
