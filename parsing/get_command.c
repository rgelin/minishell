#include "../srcs/minishell.h"

void	find_heredoc(char *line, t_pars *tab)
{
	int		i;
	int		n;
	int		*phere;
	char	**heredoc;

	i = 0;
	n = 0;
	while (line [i] != '\0')
	{
		if (check_quote(line, i) && line[i] == '<' && line[i + 1] == '<')
			n++;
		i++;
	}
}

void	ft_command(char *line, t_state *s)
{

}
