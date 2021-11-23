
#include "../srcs/minishell.h"


//Pour split la line en diffente string entre les pipes
void split_pipe(t_state *s)
{
	int	i;
	int	next;
	int start;

	i = 0;
	start = 0;
	next = s->pipe[i];
	while (i <=s->n_of_pipe)
	{
		next = next - start;
		s->cm[i] = ft_substr(s->line, start, next);
		s->cm[i] = ft_strtrim(s->cm[i], " ");
		i++;
		if (s->pipe[i] == -1)
		{
			next = s->eof;
			start = s->pipe[i - 1];
		}
		else
			next = s->pipe[i];
		start = s->pipe[i - 1] + 1;
	}
}

t_pars *split_line(t_state *s)
{
	t_pars *tab;

	tab = NULL;
	s->cm = malloc(sizeof(char *) * (s->n_of_pipe + 1));
	if (!s->cm)
	{
		write(1, "Error malloc\n", 13);
		ft_free_pars_error(s);
		exit(EXIT_FAILURE);
	}
	split_pipe(s);
	tab = find_command(s);
	//ft_free_pars(s);
	return (tab);
}
