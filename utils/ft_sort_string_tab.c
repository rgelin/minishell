/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_string_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:11:05 by rgelin            #+#    #+#             */
/*   Updated: 2022/01/11 14:50:31 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_sort_string_tab(char **tab)
{
	int		index;
	int		j;
	char	*t;

	index = 0;
	while (index < ft_tab_len(tab))
	{
		j = 0;
		while (j < ft_tab_len(tab) - 1)
		{
			if (ft_strcmp(tab[j], tab[j + 1]) > 0)
			{
				t = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = t;
			}
			j++;
		}
		index++;
	}
	tab[index] = 0;
}
