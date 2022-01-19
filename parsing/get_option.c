/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:21:10 by jlong             #+#    #+#             */
/*   Updated: 2022/01/19 10:05:11 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	return_opt(int *popt, char *line, char **options)
{
	int	i;
	int	opt;
	int	index;

	i = 0;
	opt = 0;
	while (popt[i] != -1)
	{
		index = popt[i];
		opt = index;
		while (line && line[opt] != '\0')
		{
			if (check_quote(line, opt)
				&& (line[opt] == ' ' || line[opt + 1] == '\0'))
			{
				options[i] = ft_substr(line, index, opt - (index - 1));
				options[i] = ft_strtrim(options[i], "- ");
				break ;
			}
			opt++;
		}
		i++;
	}
	options[i] = NULL;
}

char	**ft_echo_option(char *line)
{
	char	**tmp;
	int		i;
	char	**opt;

	i = 0;
	tmp = ft_split_parsing(line, ' ');
	if ((ft_strncmp(tmp[1], "-n", 3)) != 0)
		opt = NULL;
	else if (ft_strncmp(tmp[1], "-n", 3) == 0)
	{
		opt = malloc(sizeof(char *) * 2);
		if (!opt)
			exit(EXIT_FAILURE);
		opt[0] = ft_strdup(tmp[1]);
		opt[1] = NULL;
	}
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return (opt);
}
/*
char	**get_opt(char *line, char *cmd, t_pars *s)
{
	int		i;
	int		opt;
	int		*popt;
	char	**options;

	opt = 0;
	i = -1;
	options = NULL;
	(void)s;
	if (cmd && (ft_strncmp(cmd, "echo", 5) == 0))
	{
		return (ft_echo_option(line));
	}
	while (line && line[++i] != '\0')
	{
		if (line && check_quote(line, i) && line[i] == '-')
			opt++;
	}
	popt = get_index(line, opt, '-');
	options = malloc(sizeof(char *) * (opt + 1));
	if (!options)
		exit(EXIT_FAILURE);
	return_opt(popt, line, options);
	free(popt);
	return (options);
}
*/
/*
void	return_opt(int	*popt, char *line, char **options)
{
	int	i;
	int	opt;
	int	index;

	i = 0;
	opt = 0;
	while (popt[i] != -1)
	{
		index = popt[i];
		opt = index;
		while (line && line[opt] != '\0')
		{
			if (check_quote(line, opt)
				&& (line[opt] == ' ' || line[opt + 1] == '\0'))
			{
				options[i] = ft_substr(line, index, opt - (index - 1));
				options[i] = ft_strtrim(options[i], "- ");
				break ;
			}
			opt++;
		}
		i++;
	}
	options[i] = NULL;
}*/

char	**get_opt(char *line, int n, char **env)
{
	char	**tmp;
	int		i;
	int		m;
	char	**tab;

	i = 1;
	m = 0;
	tab = malloc(sizeof(char *) * (n + 1));
	if (!tab)
		exit(EXIT_FAILURE);
	tmp = ft_split_parsing(line, ' ');
	tmp = ft_arg(tmp, env);
	while (tmp && check_is_opt(tmp[i]))
	{
		tab[m] = ft_strdup(tmp[i]);
		tab[m] = ft_strtrim(tab[m], "- ");
		m++;
		i++;
	}
	tab[m] = NULL;
	ft_free(tmp, ft_tabsize(tmp));
	return (tab);
}
