
#include "minishell.h"

void	get_index(t_state *s)
{
	int	i;
	int	j;
	int	k;
	int	l;

	j = -1;
	k = -1;
	l = -1;
	i = -1;
	while (s->line[++i] != '\0')
	{
		if (s->line[i] == 34)
			s->dq[++j] = i;
		if (s->line[i] == 39)
			s->sq[++k] = i; 
		if (s->line[i] == 124)
			s->pipe[++l] = i;
		//if (s->line[i] == 36)
		//	s->n_of_dol++;
	}
}

void	check_parsing(t_state *s)
{
	if (s->n_of_dq != 0)
		s->dq = malloc(sizeof(int) * s->n_of_dq);
	if (s->n_of_sq != 0)
		s->sq = malloc(sizeof(int) * s->n_of_sq);
	//if (s->n_of_pipe != 0)
	//	s->pipe = malloc(sizeof(int) * s->n_of_pipe);
	//s->command = malloc(sizeof(char ) * (s->n_of_pipe + 1));
	get_index(s);
}

void	parsing(t_state *s)
{
	int	i;

	i = -1;
	while (s->line[++i] != '\0')
	{
		if (s->line[i] == 34)
			s->n_of_dq++;
		if (s->line[i] == 39)
			s->n_of_sq++;
		if (s->line[i] == 124)
			s->n_of_pipe++;
		if (s->line[i] == 36)
			s->n_of_dol++;
	}
	s->eof = i;
	check_parsing(s);
}

/*
//si il y a deux | d affile cest une erreur;
void	check_pipe(t_state *s)
{
	int i;

	i = 0;
	s->n_of_pipe = 0;
	s->eof = 0;
	while (s->line[i])
	{
		if (s->line[i] == 124)
		{
			s->n_of_pipe = s->n_of_pipe + 1;
		}
		i++;
	}
	get_index_pipe(t_state *s);
	s->eof = i;
}
*/
/*void	parsing(t_state *s)
{
	check_quote(s);
	if (s->n_of_sq == 0 && s->n_of_dq == 0)
	{
		check_pipe(s);
	}
}
*/
