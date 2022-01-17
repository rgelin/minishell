/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:33:50 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/17 11:19:36 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_simple(char *heredoc, int *fds, int n_pipe)
{
	int		fd;
	char	*line;

	(void)fds;
	(void)n_pipe;
	fd = open("/tmp/heredoc.txt", O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_perror("open", NULL, "Error open heredoc");
		g_global.exit_code = 1;
		return ;
	}
	line = readline("> ");
	if (ft_strcmp(line, heredoc) == 0)
		return (free(line));
	ft_putendl_fd(line, fd);
	while (ft_strcmp(line, heredoc) != 0)
	{
		free(line);
		line = readline("> ");
		if (ft_strcmp(line, heredoc) != 0)
			ft_putendl_fd(line, fd);
	}
	free(line);
	close(fd);
}

void	ft_heredoc(t_exc cmd, int *fds, int n_pipe)
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
			ft_simple(cmd.heredoc[i], fds, n_pipe);
		exit(EXIT_SUCCESS);
	}
	waitpid(0, &status, 0);
	g_global.in_heredoc = 0;
	return ;
}
