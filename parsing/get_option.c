/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:21:10 by jlong             #+#    #+#             */
/*   Updated: 2022/01/19 12:25:29 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	**ft_echo_option(int n)
{
	char	**tmp;

	tmp = NULL;
	tmp = malloc(sizeof(char *) * (n + 1));
	if (!tmp)
		exit(EXIT_FAILURE);
	if (n == 1)
	{
		tmp[0] = ft_strdup("-n");
		tmp[1] = NULL;
	}
	else
		tmp[0] = NULL;
	return (tmp);
}

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
