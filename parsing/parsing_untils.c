/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_untils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:21:22 by jlong             #+#    #+#             */
/*   Updated: 2022/01/17 15:11:53 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	ft_get_index(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ' || s[i] == '<' || s[i] == '>')
			return (i);
		i++;
	}
	return (0);
}

void	init_ptn(t_exc *tab)
{
	tab->cmd = NULL;
	tab->opt = NULL;
	tab->arg = NULL;
	tab->input = NULL;
	tab->output = NULL;
	tab->redirect = NULL;
	tab->heredoc = NULL;
}

void	init_tmp(t_tmp *tmp)
{
	tmp->tmp = NULL;
	tmp->rest = NULL;
	tmp->new_line = NULL;
	tmp->n = 0;
	tmp->m = 0;
	tmp->nl = NULL;
	tmp->var = NULL;
}

int	*get_index(char *line, size_t size, char c)
{
	int	i;
	int	j;
	int	*p_tab;

	j = 0;
	i = 0;
	p_tab = 0;
	p_tab = malloc(sizeof(int *) * (size + 1));
	if (!p_tab)
		exit(EXIT_FAILURE);
	while (line[i] != '\0')
	{
		if (c == '-' && line[i] == '-' && line[i -1] != ' ')
			i++;
		if (line[i] == c && check_quote(line, i))
			p_tab[j++] = i;
		i++;
	}
	p_tab[j] = -1;
	return (p_tab);
}

char	*our_getenv(char *line, char **env)
{
	int		index;
	char	*var;
	char	*tmp;
	char	**test;

	var = NULL;
	test = NULL;
	index = find_var_in_env(line, env);
	if (index >= 0)
	{
		var = env[index];
		test = ft_split(var, '=');
		if (!test[1])
			return (ft_strdup(""));
		tmp = ft_strdup(test[1]);
	}
	if (index == -1)
		tmp = ft_strdup("");
	index = -1;
	while (test && test[++index] != NULL)
		free(test[index]);
	if (test != NULL)
		free(test);
	free(line);
	return (ft_strtrim(tmp, " "));
}
