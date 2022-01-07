#include "../srcs/minishell.h"

int		nbr_of_heredoc(char *line)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (check_quote(line, i) && line[i] == '>' && line[i] == '>')
			n++;
		i++;
	}
	return (n);
}

char	*cut_heredoc(char *line, int index, t_state *s)
{
	char	*tmp;
	char	*rest;
	char	*new_line;
	char	*var;
	int		n;
	int		m;
	char	*nl;

	n = index;
	m = 0;
	tmp = NULL;
	var = NULL;
	nl = NULL;
	rest = NULL;
	tmp = ft_substr(line, 0, index);
	new_line = NULL;
	while (line[n] != '\0')
	{
		if (line[n] == ' ' || line[n] == '\0')
			break ;
		n++;
		m++;
	}
	nl = ft_substr(line, index + 1, m - 1);
	var = our_getenv(ft_strtrim(nl, "$"), env);
	rest = ft_substr(line, index + m, (ft_strlen(line) - index));
	new_line = ft_strjoin_double_free(tmp, var);
	new_line = ft_strjoin_double_free(new_line, rest);
	free(line);
	line = NULL;
	return (new_line);
}

char	**get_heredoc(char *line, t_state *s)
{
	int		i;
	char	*new_line;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '>' && line[i + 1] == '>')
		{
			new_line = insert_exit_code(line, i);
			line = new_line;
			i = -1;
		}
		i++;
	}
	return (new_line);
}
