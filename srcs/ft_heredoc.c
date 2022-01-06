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
	{
		g_global.exit_code = 1;
		return ;
	}
	if (pid == 0)
	{
		i = -1;
		while (heredoc[++i])
			ft_simple(heredoc[i]);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
	g_global.exit_code = 0;
}
