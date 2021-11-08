
#include "minishell.h"
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
	free(s->line);
}

void split_line(t_state *s)
{
	s->cm = malloc(sizeof(char *) * (s->n_of_pipe + 1));
	if (!s->cm)
	{
		free(s->cm);
		//return (0);
	}
	split_pipe(s);
	find_command(s);
}

/*
void split_line(t_state *s)
{
	s->cm = malloc(sizeof(char *) * (s->n_of_pipe + 1));
	if (!s->cm)
	{
		free(s->cm);
		//return (0);
	}
	//si le nombre de pipe est de 0
	if (s->n_of_pipe == 0)
	{
		s->cm[0] = ft_substr(s->line, 0, s->eof);
		//regarder par rapport au redirection
		//fonction qui free la line
	}
	//si il y a plusieurs pipe
	else
	{
		split_pipe(s);
	}
}
*/
