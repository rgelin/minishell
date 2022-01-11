#include "../srcs/minishell.h"

void	ft_free_pars_tab(t_state *s)
{
	int	nbr;

	nbr = 0;
	if (s->pipe)
		free(s->pipe);
	while (nbr <= s->n_of_pipe)
	{
		if (s->cm[nbr] != NULL || s->cm[nbr][0] == '\0')
			free ((void*)s->cm[nbr]);
		nbr++;
	}
	if (s->cm)
		free(s->cm);
}

void	ft_free_pars_error(t_state *s)
{
	int	nbr;

	nbr = 0;
	if (s->line)
		free(s->line);
	if (s->pipe)
		free(s->pipe);
	if (s->cm)
	{
		while (nbr <= s->n_of_pipe)
		{
			free(s->cm[nbr]);
			nbr++;
		}
	}
	if (s)
		free(s);
}
