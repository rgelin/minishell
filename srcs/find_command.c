
#include "minishell.h"

void	get_option(t_state *s, int index)
{

}

void	get_command(t_state *s, int index)
{

}

void	find_command(t_state *s)
{
	int	i;

	i = 0;
	s->cmd = malloc(sizeof(s->cmd) * (s->n_of_pipe + 1));
	if (!s->cmd)
	{
		free(s->cmd);
		//fonction free
		//return (0);
	}
	while (i <= s->n_of_pipe)
	{
		if (s->n_of_opt > 0)
		{
			get_command(s, i);
		}

		i++;
	}
}
