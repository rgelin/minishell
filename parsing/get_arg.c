/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:21:03 by jlong             #+#    #+#             */
/*   Updated: 2022/01/16 15:19:06 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	**return_arg_echo(char **tab, int n)
{
	int		j;
	int		i;
	char	**arg;
	char	**tmp;

	tmp = tab;
	arg = NULL;
	j = 0;
	i = 1;
	arg = malloc(sizeof(char *) * (n + 1));
	if (!arg)
		exit(EXIT_FAILURE);
	while (tmp[i] && ft_strncmp(tmp[i], "-n", 3) == 0)
		i++;
	while (i < ft_tabsize(tmp))
	{
		if (*tmp[i] == '<' || *tmp[i] == '>')
			i++;
		else if (tmp[i - 1][0] == '>' || tmp[i - 1][0] == '<')
			i++;
		else
			arg[j++] = ft_strdup(tmp[i++]);
	}
	arg[j] = NULL;
	return (arg);
}

char	**ft_echo_arg(char *line)
{
	char	**tmp;
	int		i;
	char	**arg;
	int		n;

	n = 0;
	i = 1;
	arg = NULL;
	tmp = ft_split_parsing(line, ' ');
	while (tmp[i] && ft_strncmp(tmp[i], "-n", 3) == 0)
		i++;
	while (i < ft_tabsize(tmp))
	{
		if (tmp[i][0] == '<' || tmp[i][0] == '>')
			i++;
		else if (tmp[i - 1][0] == '>' || tmp[i - 1][0] == '<')
			i++;
		else if (n++ && i++)
			continue ;
	}
	arg = return_arg_echo(tmp, n);
	ft_free(tmp, ft_tabsize(tmp));
	return (arg);
}

char	**return_arg(char **tab, int n)
{
	int		j;
	int		i;
	char	**arg;
	char	**tmp;

	tmp = tab;
	arg = NULL;
	j = 0;
	i = 0;
	arg = malloc(sizeof(char *) * (n + 1));
	if (!arg)
		exit(EXIT_FAILURE);
	while (tmp[++i] != NULL)
	{
		if (*tmp[i] == '<' || *tmp[i] == '>')
			break ;
		if (*tmp[i] != '-' && *tmp[i] != '<' && *tmp[i] != '>')
		{
			arg[j] = ft_strdup(tmp[i]);
			j++;
		}
	}
	arg[j] = NULL;
	return (arg);
}

char	**get_arg(char *line, char *cmd)
{
	char	**arg;
	char	**tmp;
	int		i;
	int		n;

	n = 0;
	i = 1;
	if (cmd && (ft_strncmp(cmd, "echo", 5) == 0))
		return (ft_echo_arg(line));
	tmp = ft_split_parsing(line, ' ');
	while (tmp[i] != NULL)
	{
		if (*tmp[i] == '<' || *tmp[i] == '>')
			break ;
		if (*tmp[i] != '-' && *tmp[i] != '<' && *tmp[i] != '>')
			n++;
		i++;
	}
	arg = return_arg(tmp, n);
	i = -1;
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
	return (arg);
}
