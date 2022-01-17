/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:20:55 by jlong             #+#    #+#             */
/*   Updated: 2022/01/17 17:57:52 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	init_tab(t_pars *tab)
{
	tab->command = NULL;
	tab->option = NULL;
	tab->arg = NULL;
	tab->heredoc = NULL;
	tab->next_char = NULL;
	tab->redirect = NULL;
}

char	*ft_get_command(char *line, char **env)
{
	char	**split;
	t_tmp	tmp;

	init_tmp(&tmp);
	split = NULL;
	split = ft_split_parsing(line, ' ');
	if (split[0][0] == '>' || split[0][0] == '<')
	{
		if (ft_tabsize(split) > 2)
		{
			tmp.tmp = ft_strdup(split[2]);
			tmp.new_line = ft_arg_bis(tmp.tmp, env);
		}
	}
	else
	{
		tmp.tmp = ft_strdup(split[0]);
		tmp.new_line = ft_arg_bis(tmp.tmp, env);
	}
	ft_free(split, ft_tabsize(split));
	//printf("tmp.new_line = %s\n", tmp.new_line);
	return (tmp.new_line);
}

t_pars	get_command(char *line, t_state *s, char **env)
{
	int		next;
	t_pars	tab;
	char	*new_line;

	(void)s;
	init_tab(&tab);
	(void)env;
	new_line = get_heredoc(line, &tab);;
	if (new_line && ft_get_index(new_line) != 0)
	{
		next = ft_get_index(new_line);
		//tab.command = ft_substr(new_line, 0, next);
		//tab.command = ft_strtrim(tab.command, " ");
		//ft_get_command(new_line, env);
		tab.command = ft_get_command(new_line, env);
		tab.option = get_opt(new_line, tab.command);
		tab.redirect = get_redirect(new_line);
		tab.arg = get_arg(new_line, tab.command);
	}
	else if (new_line)
	{
		tab.command = ft_substr(new_line, 0, ft_strlen(new_line));
		tab.command = ft_strtrim(tab.command, " ");
	}
	free(new_line);
	return (tab);
}

t_pars	*find_command(t_state *s, char **env)
{
	int		i;
	t_pars	*comd;

	i = -1;
	comd = malloc(sizeof(t_pars) * (s->n_of_pipe + 1));
	if (!comd)
		exit(EXIT_FAILURE);
	while (++i <= s->n_of_pipe)
		comd[i] = get_command(s->cm[i], s, env);
	return (comd);
}
