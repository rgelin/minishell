
#include "minishell.h"

//surement la mettre en int et verifie le nombre de 
//simple quote. n_of_sq % 2 != 0 du coup cest une error.
// et quitter la fonction sans malloc
//puis si il y a pas de double ou simple quote je peux direct verif et pipe
//return direct la fonction pipe si il y a pas de quote ?

//Dans un deuxieme temps verifier si le cas ou il y a des quote.

int	get_index(t_state *s, int *p_tab, size_t size, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	p_tab = ft_calloc((size + 1), sizeof(int));
	if (!p_tab)
	{
		free(p_tab);
		return (0);
	}
	printf("char = %c\n", c);
	while (s->line[i] != '\0')
	{
		if (s->line[i] == c)
		{
			p_tab[j] = i;
			printf("index = %d\n", p_tab[j]);
		}
		j++;
		i++;
	}
	p_tab[j] = -1;
	printf("-index = %d\n", p_tab[j]);
	return (1);
}

int	check_parsing(t_state *s)
{
	if (s->n_of_sq > 0)
		if (!get_index(s, s->sq, s->n_of_sq, (char)39))
			return (0);
	if (s->n_of_dq > 0)
		if (!get_index(s, s->dq, s->n_of_dq, (char)34))
			return (0);
	if (s->n_of_pipe >= 0)
	{
		if (!get_index(s, s->pipe, s->n_of_pipe, (char)124))
			return (0);
	}
	if (s->n_of_dol > 0)
		if (!get_index(s, s->dol, s->n_of_dol, (char)36))
			return (0);
	return (1);
}
/*
int	*get_index(t_state *s, size_t size, char c)
{
	int	i;
	int	j;
	int *p_tab;

	j = 0;
	i = 0;
	p_tab = ft_calloc((size + 1), sizeof(int));
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
		}
		j++;
		i++;
	}
	return (p_tab);
}

int	check_parsing(t_state *s)
{
	if (s->n_of_sq > 0)
		s->sq = get_index(s, s->n_of_sq, (char)39);
	if (s->n_of_dq > 0)
		s->dq = get_index(s, s->n_of_dq, (char)34);
	if (s->n_of_pipe >= 0)
		s->pipe = get_index(s, s->n_of_pipe, (char)124);
	if (s->n_of_dol > 0)
		s->dol = get_index(s, s->n_of_dol, (char)36);
	return (1);
}
*/
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
	}
	s->eof = i;
}

int	parsing(t_state *s)
{
	check_char(s);
	if (check_parsing(s))
	{
		if (s->n_of_dq == 0 && s->n_of_sq == 0)
		{
			split_line(s);
		}
	}
	return (1);
}
