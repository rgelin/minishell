/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:33:50 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/13 03:26:03 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **ft_realloc(char **tab)
{
	int	i;
	char **res;
	
	i = -1;
	res = malloc(sizeof(char *) * (ft_tabsize(tab) + 2));
	if (!res)
		exit(EXIT_FAILURE);
	while (tab[++i])
		res[i] = tab[i];
	return (res);
}

static char	**ft_simple(char *heredoc)
{
	char	**line;
	int		i;

	line = malloc(sizeof(char *) + 1);
	if (!line)
		exit(EXIT_FAILURE);
	rl_on_new_line();
	i = -1;
	line[++i] = readline("> ");
	line[++i] = NULL;
	i = 0;
	while (ft_strcmp(line[i], heredoc) != 0)
	{
		line = ft_realloc(line);
		line[++i] = readline("> ");
		line[i + 1] = NULL;
	}
	return (line);
}

static void	ft_iscat(t_exc cmd)
{
	if (cmd.cmd)
	{
		if (!ft_strcmp(cmd.cmd, "cat"))
		{
			free(cmd.cmd);
			cmd.cmd = ft_strdup("");
		}
	}
}

void	ft_heredoc(t_exc cmd)
{
	int	i;
	int	status;

	if (cmd.heredoc == NULL)
		return ;
	ft_iscat(cmd);
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
