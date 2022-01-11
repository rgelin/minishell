#include "minishell.h"

static void	ft_simple(char *heredoc)
{
	char	*line;

	rl_on_new_line();
	line = readline("> ");
	while (ft_strcmp(line, heredoc) != 0)
		line = readline("> ");
}

void	ft_heredoc(t_exc cmd)
{
	int	i;
	int	status;

	if (cmd.heredoc == NULL)
		return ;
	g_global.in_heredoc = 1;
	g_global.fork_pid = fork();
	if (g_global.fork_pid == -1)
		return ;
	if (g_global.fork_pid == 0)
	{
		ft_set_signal();
		i = -1;
		while (cmd.heredoc[++i])
			ft_simple(cmd.heredoc[i]);
		exit(EXIT_SUCCESS);
	}
	waitpid(0, &status, 0);
	g_global.in_heredoc = 0;
	return ;
}
