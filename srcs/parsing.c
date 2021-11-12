
#include "minishell.h"

//surement la mettre en int et verifie le nombre de 
//simple quote. n_of_sq % 2 != 0 du coup cest une error.
// et quitter la fonction sans malloc
//puis si il y a pas de double ou simple quote je peux direct verif et pipe
//return direct la fonction pipe si il y a pas de quote ?

//Dans un deuxieme temps verifier si le cas ou il y a des quote.

void	ft_free_pars_tab(t_state *s)
{
	if (s->pipe)
		free(s->pipe);
	if (s->line)
		free(s->line);
	if (s)
		free(s);
}

// check le nbr de pipe et donner ces indices + verifie les sq
int	check_parsing(t_state *s)
{
	if (!check_quote(s->line, s->eof))
	{
		//PROBLEME DE FREE
		//ft_free_pars_tab(s);
		exit(EXIT_FAILURE);
	}
	if (s->n_of_pipe >= 0)
		s->pipe = get_index(s->line, (s->n_of_pipe + 1), '|');
	return (1);
}
//verifie si on est dans un simple ou double quote
int	check_quote(char *line, int	index)
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
//trouver le bon nombre de pipe
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
	t_pars *tab;

	tab = NULL;
	check_char(s);
	if (check_parsing(s))
	{
		tab = split_line(s);
	}
	ft_free_pars_tab(s);
	return (tab);
}
