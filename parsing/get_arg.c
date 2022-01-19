/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:21:03 by jlong             #+#    #+#             */
/*   Updated: 2022/01/19 10:03:15 by jlong            ###   ########.fr       */
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
/*
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
}*/
/*
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
	ft_free(tmp, ft_tabsize(tmp));
	return (arg);
}
*/

int		check_is_opt(char *line)
{
	int	i;

	i = 0;
	if (line && line[i] == '-' && line[i + 1] != '\0')
	{
		i++;
		while (line[i] != '\0')
		{
			if (line[i] == ' ')
			{
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

char	**return_arg(char *line, char **env, int n, int index)
{
	char	**tmp;
	int		m;
	char	**tab;

	m = 0;
	tab = malloc(sizeof(char *) * (n + 1));
	if (!tab)
		exit(EXIT_FAILURE);
	tmp = ft_split_parsing(line, ' ');
	tmp = ft_arg(tmp, env);
	while (tmp && tmp[index])
	{
		tab[m] = ft_strdup(tmp[index]);
		m++;
		index++;
	}
	tab[m] = NULL;
	ft_free(tmp, ft_tabsize(tmp));
	return (tab);
}

void	get_arg(char *line, char *cmd, char **env, t_pars *tab)
{
	char	**tmp;
	int		i;
	int		n;
	int		start;

	n = 0;
	i = 1;
	(void)cmd;
	//if (cmd && (ft_strncmp(cmd, "echo", 5) == 0))
	//	return (ft_echo_arg(line));
	tmp = ft_split_parsing(line, ' ');
	tmp = ft_arg(tmp, env);
	while (check_is_opt(tmp[i]))
	{
		i++;
		n++;
	}
	//fonction qui va crée le tab de option et mettre les options dedans
	tab->option = get_opt(line, n, env);
	n = 0;
	start = i;
	while (tmp && tmp[i])
	{
		i++;
		n++;
	}
	// et apres le reste on va mettre dans les arguments
	tab->arg = return_arg(line, env, n, start);
	ft_free(tmp, ft_tabsize(tmp));
}
