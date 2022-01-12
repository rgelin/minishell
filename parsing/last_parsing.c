/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:21:19 by jlong             #+#    #+#             */
/*   Updated: 2022/01/12 13:07:21 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	*option(char **options)
{
	char	*line;
	int		i;
	int		size;

	size = 0;
	i = 0;
	if (options[i] == NULL)
		return (NULL);
	while (options[i])
	{
		size = size + ft_strlen(options[i]);
		i++;
	}
	line = malloc(sizeof(line) * (size + 2));
	if (!line)
		exit(EXIT_FAILURE);
	i = -1;
	line[0] = '-';
	line[1] = '\0';
	while (options[++i])
	{
		line = ft_strcat(line, options[i]);
		free(options[i]);
	}
	return (line);
}

char	*ft_command(char *command)
{
	int		i;
	char	*new;

	i = 0;
	if (!command)
		return (NULL);
	while (command[i] != '\0')
	{
		command[i] = ft_tolower(command[i]);
		i++;
	}
	new = ft_strdup(command);
	free(command);
	return (new);
}

char	*new_redirect(char *line)
{
	int		i;
	t_tmp	tmp;

	init_tmp(&tmp);
	i = 0;
	while (line[i] == '>' || line[i] == '<')
		i++;
	tmp.tmp = ft_substr(line, 0, i);
	while (line[i] && line[i] == ' ')
		i++;
	tmp.n = i;
	while (line[i] && ft_isascii(line[i]) && line[i] != ' ')
		i++;
	tmp.var = ft_substr(line, tmp.n, i - tmp.n);
	tmp.new_line = ft_strjoin_double_free(tmp.tmp, tmp.var);
	free(line);
	line = NULL;
	//free(tmp.tmp);
	//free(tmp.var);
	return (tmp.new_line);
}

char	**get_redirect_bis(char **tab_redirect)
{
	int		i;
	char	**new;

	new = NULL;
	i = 0;
	while (tab_redirect[i])
	{
		tab_redirect[i] = new_redirect(tab_redirect[i]);
		i++;
	}
	new = tab_redirect;
	return (new);
}

t_exc	*last_parsing(t_pars *tab, char **env)
{
	int		i;
	t_exc	*last_tab;

	last_tab = NULL;
	last_tab = malloc(sizeof(t_exc) * (tab->pipe + 1));
	if (!last_tab)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < tab->pipe + 1)
	{
		init_ptn(&last_tab[i]);
		if (tab[i].command)
			last_tab[i].cmd = ft_command(tab[i].command);
		if (tab[i].option)
			last_tab[i].opt = option(tab[i].option);
		if (tab[i].redirect)
			last_tab[i].redirect = get_redirect_bis(tab[i].redirect);
		if (tab[i].heredoc)
			last_tab[i].heredoc = tab[i].heredoc;
		if (tab[i].arg)
			last_tab[i].arg = ft_arg(tab[i].arg, env);
		i++;
	}
	return (last_tab);
}
