
#include "minishell.h"

//surement la mettre en int et verifie le nombre de 
//simple quote. n_of_sq % 2 != 0 du coup cest une error.
// et quitter la fonction sans malloc
//puis si il y a pas de double ou simple quote je peux direct verif et pipe
//return direct la fonction pipe si il y a pas de quote ?

//Dans un deuxieme temps verifier si le cas ou il y a des quote.

int	*get_index(t_state *s, size_t size, char c)
{
	int	i;
	int	j;
	int *p_tab;

	j = 0;
	i = 0;
	p_tab = malloc(sizeof(int*) * (size + 1));
	if (!p_tab)
	{
		free(p_tab);
		return (0);
	}
	while (s->line[i] != '\0')
	{
		if (s->line[i] == c)
		{
			p_tab[j] = i;
			j++;
		}
		i++;
	}
	p_tab[j] = -1;
	return (p_tab);
}

int	check_parsing(t_state *s)
{
	if (s->n_of_sq > 0)
		s->sq = get_index(s, s->n_of_sq, '\'');
	if (s->n_of_dq > 0)
		s->dq = get_index(s, s->n_of_dq, '"');
	if (s->n_of_pipe >= 0)
		s->pipe = get_index(s, (s->n_of_pipe + 1), '|');
	if (s->n_of_dol > 0)
		s->dol = get_index(s, s->n_of_dol, '$');
	if (s->n_of_opt > 0)
		s->opt = get_index(s, s->n_of_opt, '-');
	if (s->n_of_lchv > 0)
		s->lchv = get_index(s, s->n_of_lchv, '<');
	if (s->n_of_rchv > 0)
		s->rchv = get_index(s, s->n_of_rchv, '>');
	return (1);
}

void check_char(t_state *s)
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
		if (s->line[i] == 45)
			s->n_of_opt++;
		if (s->line[i] == 60)
			s->n_of_lchv++;
		if (s->line[i] == 62)
			s->n_of_rchv++;
	}
	s->eof = i;
}

int	parsing(t_state *s)
{
	check_char(s);
	if (check_parsing(s))
	{
		//si le nombre de quote est de 0 et sans redicrection.
		if (s->n_of_dq == 0 && s->n_of_sq == 0 && s->n_of_lchv == 0
				&& s->n_of_rchv == 0)
		{
			split_line(s);
		}
	/*	else if (s->n_of_dq == 0 && s->n_of_sq == 0)
		{

		}
		else
		{
		}
		*/
	}
	return (1);
}
