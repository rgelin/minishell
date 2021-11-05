
#include "minishell.h"

void	check_quote(t_state *state)
{
	int	i;
	int	n_of_sq;
	int	n_of_dq;

	i = 0;
	n_of_sq = 0;
	n_of_dq = 0;
	while (state->line[i] != '\0')
	{
		if (state->line[i] == 34)
			n_of_dq++;
		if (state->line[i] == 39)
			n_of_sq++;
		i++;
	}
	if (n_of_sq != 0)
		state->sq = malloc(sizeof(int) * n_of_sq);
	if (n_of_dq != 0)
		state->dq = malloc(sizeof(int) * n_of_dq);
	//if (!state->dq || !state->sq)
		//fonction free
	//get_index_quote(state); 
}
/*
int		parsing(t_state *line)
{
	char	*tmp;

	tmp = line;
	while (tmp)
	{

	}
	return (1);
}
*/
