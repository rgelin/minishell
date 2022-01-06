#include "minishell.h"

static void	ft_simple(char *heredoc)
{
	char	*line;

	rl_on_new_line();
	line = readline("> ");
	while (ft_strcmp(line, heredoc) != 0 && line != '\0')
		line = readline("> ");
}

void	ft_heredoc(char **heredoc)
{
	int	i;
	int	pid;
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		i = -1;
		while (heredoc[++i])
			ft_simple(heredoc[i]);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
	free(heredoc[0]);
	free(heredoc);
}
