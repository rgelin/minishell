
#include "minishell.h"

void	get_index_quote(t_state *state)
{
	int i;
	int j;
	int k;

	j = 0;
	k = 0;
	i = 0;
	while (state->line[i] != '\0')
	{
		if (state->line[i] == 34)
		{
			state->dq[j] = i;
			j++;
		}
		if (state->line[i] == 39)
		{
			state->sq[k] = i;
			k++;
		}
		i++;
	}
}
//surement la mettre en int et verifie le nombre de 
//simple quote. n_of_sq % 2 != 0 du coup cest une error.
// et quitter la fonction sans malloc
//puis si il y a pas de double ou simple quote je peux direct verif et pipe
//return direct la fonction pipe si il y a pas de quote ?

//Dans un deuxieme temps verifier si le cas ou il y a des quote.
void	check_quote(t_state *state)
{
	int	i;

	i = 0;
	state->n_of_sq = 0;
	state->n_of_dq = 0;
	while (state->line[i] != '\0')
	{
		if (state->line[i] == 34)
			state->n_of_dq++;
		if (state->line[i] == 39)
			state->n_of_sq++;
		i++;
	}
	//fonction verife du nombre de single quote;
	if (state->n_of_sq != 0)
		state->sq = malloc(sizeof(int) * state->n_of_sq);
	if (state->n_of_dq != 0)
		state->dq = malloc(sizeof(int) * state->n_of_dq);
	//if (!state->dq || !state->sq)
		//fonction free
	get_index_quote(state); 
}
