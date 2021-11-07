
#include "minishell.h"

void split_pipe(t_state *s)
{
	int	i;
	int	next;
	int start;

	i = 0;
	start = 0;
	next = s->pipe[i];
	printf("ici\n");
	while (s->pipe[i])
	{
		next = next - start;
		s->cm[i] = ft_substr(s->line, start, next);
		start = next;
		if (s->pipe[i] == 0)
			next = s->eof;
		else
			next = s->pipe[i];
		i++;
	}	
}

void split_line(t_state *s)
{
	s->cm = malloc(sizeof(char *) * (s->n_of_pipe + 1));
	if (!s->cm)
	{
		free(s->cm);
	}
	if (s->n_of_pipe == 0)
	{
		s->cm[0] = ft_substr(s->line, 0, s->eof);
		//fonction qui free la line
	}
	/*else
	{
		split_pipe(s);
	}
	*/
}
